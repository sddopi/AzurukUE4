

#include "Azuruk.h"
#include "AzurukBaseCharacter.h"

const uint8 DEFAULTFEATURE = uint8(0);

AAzurukBaseCharacter::AAzurukBaseCharacter(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// Azuruk Defaults
	Health = 100.f;
	maxMorphTime = 20.f;

	// Configure character movement
	CharacterMovement->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	CharacterMovement->RotationRate = FRotator(0.0f, 560.0f, 0.0f); // ...at this rotation rate
	CharacterMovement->JumpZVelocity = 600.f;
	CharacterMovement->AirControl = 0.2f;

	// Initial bool setup
	bIsCasting = false;
}

void AAzurukBaseCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (Mesh->SkeletalMesh && Mesh->GetAnimInstance())
	{
		defaultCharacterFeature = NewObject<UAzurukCharacterFeatures>(this, UAzurukCharacterFeatures::StaticClass());
	}	

	if (Role = ROLE_Authority)
	{
		Health = GetMaxHealth();
	}
}

AAzurukBaseCharacter* AAzurukBaseCharacter::GetBaseCharacter()
{
	return this;
}

//////////////////////////////////////////////////////////////////////////
// Animations

float AAzurukBaseCharacter::PlayAnimMontage(class UAnimMontage* AnimMontage, float InPlayRate, FName StartSectionName)
{
	USkeletalMeshComponent* UseMesh = Mesh;
	if (AnimMontage && UseMesh && UseMesh->AnimScriptInstance)
	{
		return UseMesh->AnimScriptInstance->Montage_Play(AnimMontage, InPlayRate);
	}
	return 0.0f;
}

void AAzurukBaseCharacter::StopAnimMontage(class UAnimMontage* AnimMontage)
{
	USkeletalMeshComponent* UseMesh = Mesh;
	if (AnimMontage && UseMesh && UseMesh->AnimScriptInstance &&
		UseMesh->AnimScriptInstance->Montage_IsPlaying(AnimMontage))
	{
		UseMesh->AnimScriptInstance->Montage_Stop(AnimMontage->BlendOutTime);
	}
}

void AAzurukBaseCharacter::StopAllAnimMontages()
{
	USkeletalMeshComponent* UseMesh = Mesh;
	if (UseMesh && UseMesh->AnimScriptInstance)
	{
		UseMesh->AnimScriptInstance->Montage_Stop(0.0f);
	}
}

//////////////////////////////////////////////////////////////////////////
// Vitals

float AAzurukBaseCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser)
{
	if (!ShouldTakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser))
	{
		return 0.f;
	}

	const float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	if (ActualDamage > 0.f)
	{
		ModifyHealth(ActualDamage);

		if (GetHealth() <= 0)
		{
			Die(ActualDamage, DamageEvent, EventInstigator, DamageCauser);
		}
		else
		{
			// Hit
		}
		// Cause a Noise
		MakeNoise(1.0f, EventInstigator ? EventInstigator->GetPawn() : this);
	}

	return Damage;
}

bool AAzurukBaseCharacter::CanDie(float KillingDamage, FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser) const
{
	if (bIsDying										// already dying
		|| IsPendingKill()								// already destroyed
		|| Role != ROLE_Authority						// not authority
		|| GetWorld()->GetAuthGameMode() == NULL
		|| GetWorld()->GetAuthGameMode()->GetMatchState() == MatchState::LeavingMap)	// level transition occurring
	{
		return false;
	}

	return true;
}

void AAzurukBaseCharacter::Die(float KillingDamage, struct FDamageEvent const& DamageEvent, class AController* Killer, class AActor* DamageCauser)
{
	if (CanDie(KillingDamage, DamageEvent, Killer, DamageCauser))
	{
		if (bIsDying)
		{
			return;
		}

		bReplicateMovement = false;
		bTearOff = true;
		bIsDying = true;

		DetachFromControllerPendingDestroy();

		// disable collisions on capsule
		CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		CapsuleComponent->SetCollisionResponseToAllChannels(ECR_Ignore);

		if (Mesh)
		{
			static FName CollisionProfileName(TEXT("Ragdoll"));
			Mesh->SetCollisionProfileName(CollisionProfileName);
		}
		SetActorEnableCollision(true);

		SetRagdollPhysics();
	}
}

void AAzurukBaseCharacter::SetRagdollPhysics()
{
	if (Mesh || Mesh->GetPhysicsAsset())
	{
		// initialize physics/etc
		Mesh->SetAllBodiesSimulatePhysics(true);
		Mesh->SetSimulatePhysics(true);
		Mesh->WakeAllRigidBodies();
		Mesh->bBlendPhysics = true;

		CharacterMovement->StopMovementImmediately();
		CharacterMovement->DisableMovement();
		CharacterMovement->SetComponentTickEnabled(false);
	}	
}

void AAzurukBaseCharacter::Destroyed()
{
	Super::Destroyed();

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), deathParticle, GetActorLocation());
}

//////////////////////////////////////////////////////////////////////////
// Health

void AAzurukBaseCharacter::ModifyHealth(float Amount)
{
	Health = FMath::IsNegativeFloat(Amount)
		// Heal 
		? FMath::Min(Health - Amount, GetMaxHealth())
		// Damage
		: FMath::Max(Health - Amount, 0.f);
}

float AAzurukBaseCharacter::GetHealth()
{
	return Health;
}

float AAzurukBaseCharacter::GetMaxHealth() const
{
	return GetClass()->GetDefaultObject<AAzurukBaseCharacter>()->GetHealth();
}

bool AAzurukBaseCharacter::IsAlive() const
{
	return Health > 0;
}

//////////////////////////////////////////////////////////////////////////
// Abilities

void AAzurukBaseCharacter::AddAbility(class AAzurukAbilityBase* Ability)
{
	if (Ability != NULL)
	{
		UE_LOG(LogTemp, Log, TEXT("ability added"));
		Ability->OnAddAbility(this);
		Abilities.AddUnique(Ability);
	}
}

void AAzurukBaseCharacter::RemoveAbility(class AAzurukAbilityBase* Ability)
{
	if (Ability != NULL)
	{
		Ability->OnRemoveAbility();
		Abilities.RemoveSingle(Ability);
	}
}

void AAzurukBaseCharacter::DestroyAbilities()
{
	// remove all abilities from pawn and destroy them
	for (int32 i = Abilities.Num() - 1; i >= 0; i--)
	{
		AAzurukAbilityBase* Ability = Abilities[i];
		if (Ability)
		{
			RemoveAbility(Ability);
			Ability->Destroy();
		}
	}
}

class AAzurukAbilityBase* AAzurukBaseCharacter::FindAbility(TSubclassOf<class AAzurukAbilityBase> AbilityClass)
{
	for (int32 i = 0; i < Abilities.Num(); i++)
	{
		if (Abilities[i] && Abilities[i]->IsA(AbilityClass))
		{
			return Abilities[i];
		}
	}

	return NULL;
}

class AAzurukAbilityBase* AAzurukBaseCharacter::FindAbilityBoundToKey(FString KeyBinding)
{
	UE_LOG(LogTemp, Log, TEXT("num abilities: %d"), Abilities.Num());
	for (int32 i = 0; i < Abilities.Num(); i++)
	{
		UE_LOG(LogTemp, Log, TEXT("keybindings: %s, %s"), *KeyBinding, *Abilities[i]->GetKeyBinding());
		if (Abilities[i] && Abilities[i]->GetKeyBinding() == KeyBinding)
		{
			UE_LOG(LogTemp, Log, TEXT("ability found"));
			return Abilities[i];
		}
	}

	return NULL;
}

void AAzurukBaseCharacter::StartAbility(FString KeyBinding)
{
	if (bIsCasting == false) {
		bIsCasting = true;
		AAzurukAbilityBase* Ability = FindAbilityBoundToKey(KeyBinding);
		UE_LOG(LogTemp, Log, TEXT("trying to use ability"));
		if (Ability != NULL)
		{
			UE_LOG(LogTemp, Log, TEXT("ability not null"));
			Ability->InputPressed();
		}
	}
}

void AAzurukBaseCharacter::StopAbility(FString KeyBinding)
{
	bIsCasting = false;
	AAzurukAbilityBase* Ability = FindAbilityBoundToKey(KeyBinding);
	if (Ability != NULL)
	{
		Ability->InputReleased();
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AAzurukBaseCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	check(InputComponent);

	/* abilities */
	InputComponent->BindAction("AbilityOne", IE_Pressed, this, &AAzurukBaseCharacter::AbilityButtonOne);
	InputComponent->BindAction("AbilityOne", IE_Released, this, &AAzurukBaseCharacter::AbilityButtonOneReleased);
}

void AAzurukBaseCharacter::AbilityButtonOne()
{
	StartAbility("1");
}

void AAzurukBaseCharacter::AbilityButtonOneReleased()
{
	StopAbility("1");
}
