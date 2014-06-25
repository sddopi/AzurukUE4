

#include "Azuruk.h"
#include "AzurukBaseCharacter.h"

const uint8 DEFAULTFEATURE = uint8(0);

AAzurukBaseCharacter::AAzurukBaseCharacter(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// Don't let Azuruk Characters die
	InitialLifeSpan = 0;

	// Rotate Mesh
	Mesh->SetRelativeRotation(FRotator(0, 0, -90));

	// Configure character movement
	CharacterMovement->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	CharacterMovement->RotationRate = FRotator(0.0f, 560.0f, 0.0f); // ...at this rotation rate
	CharacterMovement->JumpZVelocity = 600.f;
	CharacterMovement->AirControl = 0.2f;
}

void AAzurukBaseCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (Role = ROLE_Authority)
	{
		Health = GetMaxHealth();
	}
}

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

		bInRagdoll = true;
	}	
}

void AAzurukBaseCharacter::ModifyHealth(float Amount)
{
	Health = FMath::IsNegativeFloat(Amount) 
		// Heal 
		? FMath::Min(Health - Amount, GetMaxHealth())
		// Damage
		: FMath::Min(Health - Amount, 0.f);
}

float AAzurukBaseCharacter::GetHealth()
{
	return Health;
}

float AAzurukBaseCharacter::GetMaxHealth() const
{
	return GetClass()->GetDefaultObject<AAzurukBaseCharacter>()->Health;
}



