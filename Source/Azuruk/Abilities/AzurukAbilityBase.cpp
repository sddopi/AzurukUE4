

#include "Azuruk.h"
#include "AzurukAbilityBase.h"


AAzurukAbilityBase::AAzurukAbilityBase(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	bIsOnCooldown = false;
	bIsChanneled = false;
	bIsCasted = false;
	bIsInstant = false;

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bAllowTickOnDedicatedServer = true;
}

void AAzurukAbilityBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	OnAbilityInitialized();
}

//////////////////////////////////////////////////////////////////////////
// Events

void AAzurukAbilityBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsOnCooldown)
	{
		CurrentCooldownTime += DeltaTime;
		if (CurrentCooldownTime >= AbilityConfig.AbilityCooldownTime)
		{
			CurrentCooldownTime = 0;
			bIsOnCooldown = false;
		}
	}

	if (bIsChanneled)
	{
		CurrentIntervalTime += DeltaTime;
		if (CurrentIntervalTime >= AbilityConfig.ChannelInterval)
		{
			CurrentIntervalTime = 0;
			OnAbilityStart();
		}
	}

	if (bIsCasted)
	{
		CurrentCastTime += DeltaTime;
		if (CurrentCastTime >= AbilityConfig.MaxCastTime)
		{
			CurrentCastTime = 0;
			bIsOnCooldown = true;
			bIsCasted = false;
			OnAbilityStart();
		}
	}

	if (bIsCharged)
	{
		CurrentChargeTime += DeltaTime;
		if (CurrentChargeTime >= AbilityConfig.MaxCastTime)
		{
			CurrentChargeTime = 0;
			bIsCharged = false;
			OnAbilityStart();
		}
	}

	if (bIsInstant)
	{
		OnAbilityStart();
	}
}

void AAzurukAbilityBase::OnAddAbility(AAzurukBaseCharacter* NewOwner)
{
	SetAbilityOwner(NewOwner);
}

void AAzurukAbilityBase::OnRemoveAbility()
{
	SetAbilityOwner(NULL);
}

void AAzurukAbilityBase::OnAbilityStart()
{
	UE_LOG(LogTemp, Log, TEXT("ability started"));
	UseAbility();

	// reset boolean
	if (bIsInstant)
	{
		bIsInstant = false;
	}
}

void AAzurukAbilityBase::OnAbilityStop()
{
	UE_LOG(LogTemp, Log, TEXT("ability stopped"));
	// reset boolean
	if (bIsCasted)
	{
		bIsCasted = false;
	}

	if (bIsCharged)
	{
		bIsOnCooldown = true;
		bIsCharged = false;
	}
}

void AAzurukAbilityBase::OnAbilityInitialized()
{
	UE_LOG(LogTemp, Log, TEXT("ability initialized"));
	bIsAbilityInitialized = true;
}

//////////////////////////////////////////////////////////////////////////
// Input

void AAzurukAbilityBase::InputPressed()
{
	if (bIsAbilityInitialized)
	{
		UE_LOG(LogTemp, Log, TEXT("ability pressed"));
		if (!bIsOnCooldown)
		{
			if (AbilityConfig.AbilityCastType == ECastType::Casted)
			{
				bIsCasted = true;
			}
			if (AbilityConfig.AbilityCastType == ECastType::Casted_Charged)
			{
				bIsCharged = true;
			}
			if (AbilityConfig.AbilityCastType == ECastType::Channeled)
			{
				OnAbilityStart();
				bIsChanneled = true;
				bIsOnCooldown = true;
			}
			if (AbilityConfig.AbilityCastType == ECastType::Instant)
			{
				OnAbilityStart();
				bIsInstant = true;
				bIsOnCooldown = true;
			}
		}
	}
}

void AAzurukAbilityBase::InputReleased()
{
	UE_LOG(LogTemp, Log, TEXT("ability released"));
	if (AbilityConfig.AbilityCastType == ECastType::Channeled)
	{
		OnAbilityStop();
		bIsChanneled = false;
	}

	if (AbilityConfig.AbilityCastType == ECastType::Instant)
	{
		OnAbilityStop();
	}
}

void AAzurukAbilityBase::SetKeyBinding(FString NewKeyBinding)
{
	if (NewKeyBinding != KeyBinding &&
		NewKeyBinding != NULL)
	{
		KeyBinding = NewKeyBinding;
	}
}

FString AAzurukAbilityBase::GetKeyBinding()
{
	return KeyBinding;
}

//////////////////////////////////////////////////////////////////////////
// Replication

void AAzurukAbilityBase::OnRep_AbilityOwner()
{
	if (AbilityOwner)
	{
		OnAddAbility(AbilityOwner);
	}
	else
	{
		OnRemoveAbility();
	}
}

//////////////////////////////////////////////////////////////////////////
// Reading Data

void AAzurukAbilityBase::SetAbilityOwner(AAzurukBaseCharacter* NewOwner)
{
	if (NewOwner != AbilityOwner)
	{
		Instigator = NewOwner;
		AbilityOwner = NewOwner;
		SetOwner(NewOwner);
	}
}

USkeletalMeshComponent* AAzurukAbilityBase::GetOwnerMesh() const
{
	USkeletalMeshComponent* UseMesh = NULL;

	if (AbilityOwner)
	{
		UseMesh = AbilityOwner->GetController()->GetCharacter()->Mesh;
		return UseMesh;
	}

	return UseMesh;
}

//////////////////////////////////////////////////////////////////////////
// Ability Usage

UAudioComponent* AAzurukAbilityBase::PlayAbilitySound(USoundCue* Sound)
{
	UAudioComponent* AC = NULL;
	if (Sound && AbilityOwner)
	{
		AC = UGameplayStatics::PlaySoundAttached(Sound, AbilityOwner->GetRootComponent());
	}

	return AC;
}

float AAzurukAbilityBase::PlayAbilityAnimation(const FAbilityAnim& Animation)
{
	float Duration = 1.0f;
	if (AbilityOwner &&
		AbilityOwner->GetController()->GetCharacter()->IsA(AAzurukBaseCharacter::StaticClass()))
	{
		UAnimMontage* UseAnim = Animation.Pawn3P;
		AAzurukBaseCharacter* AChar = Cast<AAzurukBaseCharacter>(AbilityOwner->GetController()->GetCharacter());
		if (UseAnim)
		{
			Duration = AChar->PlayAnimMontage(UseAnim);
		}
	}

	return Duration;
}

void AAzurukAbilityBase::StopAbilityAnimation(const FAbilityAnim& Animation)
{
	if (AbilityOwner &&
		AbilityOwner->GetController()->GetCharacter()->IsA(AAzurukBaseCharacter::StaticClass()))
	{
		UAnimMontage* UseAnim = Animation.Pawn3P;
		AAzurukBaseCharacter* AChar = Cast<AAzurukBaseCharacter>(AbilityOwner->GetController()->GetCharacter());
		if (UseAnim)
		{
			AChar->StopAnimMontage(UseAnim);
		}
	}
}

FVector AAzurukAbilityBase::GetAttachLocation() const
{
	USkeletalMeshComponent* UseMesh = GetOwnerMesh();
	return UseMesh->GetSocketLocation(AttachPoint);
}

FVector AAzurukAbilityBase::GetAttachDirection() const
{
	USkeletalMeshComponent* UseMesh = GetOwnerMesh();
	return UseMesh->GetSocketRotation(AttachPoint).Vector();
}