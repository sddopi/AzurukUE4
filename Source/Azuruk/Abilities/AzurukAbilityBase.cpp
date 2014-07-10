

#include "Azuruk.h"
#include "AzurukAbilityBase.h"


AAzurukAbilityBase::AAzurukAbilityBase(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	bIsOnCooldown = false;
	bIsChanneled = false;
	bIsCasted = false;
}

void AAzurukAbilityBase::Tick(float DeltaTime)
{
	if (bIsOnCooldown)
	{
		currentCooldownTime += DeltaTime;
		if (currentCooldownTime >= AbilityCooldownTime)
		{
			currentCooldownTime = 0;
			bIsOnCooldown = false;
		}
	}

	if (bIsChanneled)
	{
		currentIntervalTime += DeltaTime;
		if (currentIntervalTime >= ChannelInterval)
		{
			currentIntervalTime = 0;
			OnAbilityStart();
		}
	}

	if (bIsCasted)
	{
		currentCastTime += DeltaTime;
		if (currentCastTime >= MaxCastTime)
		{
			currentCastTime = 0;
			bIsCasted = false;
			OnAbilityStart();
		}
	}

	if (bIsCharged)
	{
		currentChargeTime += DeltaTime;
		if (currentChargeTime >= MaxCastTime)
		{
			currentChargeTime = 0;
			bIsCharged = false;
			OnAbilityStart();
		}
	}

	if (bIsInstant)
	{
		OnAbilityStart();
	}
}

bool AAzurukAbilityBase::IsTickable() const
{
	if (AbilityOwner)
	{
		if (GetWorld())
		{
			return true;
		}
		return false;
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////
// Ability Manager

void AAzurukAbilityBase::OnAddAbility(APawn* NewOwner)
{
	SetAbilityOwner(NewOwner);
}

void AAzurukAbilityBase::OnRemoveAbility()
{
	SetAbilityOwner(NULL);
}

void AAzurukAbilityBase::SetAbilityOwner(APawn* NewOwner)
{
	if (NewOwner != AbilityOwner)
	{
		Instigator = NewOwner;
		AbilityOwner = NewOwner;
		SetOwner(NewOwner);
	}
}

UWorld* AAzurukAbilityBase::GetWorld() const
{
	if (!AbilityOwner)
		return NULL;
	UWorld* const World = GEngine->GetWorldFromContextObject(AbilityOwner);
	return World ? World : nullptr;
}

void AAzurukAbilityBase::Initialize(APawn* owner, APawn* instigator)
{
	AbilityOwner = owner;
	Instigator = instigator;

	if (AbilityOwner)
	{
		if (GetWorld())
		{
			IsAbilityInitialized = true;
			OnAbilityInitialized();
			return;
		}
		IsAbilityInitialized = false;
	}
	IsAbilityInitialized = false;
}

//////////////////////////////////////////////////////////////////////////
// Input

void AAzurukAbilityBase::InputPressed()
{
	if (IsAbilityInitialized)
	{
		if (!bIsOnCooldown)
		{
			if (AbilityCastType == ECastType::Casted)
			{
				bIsCasted = true;
				bIsOnCooldown = true;
			}
			if (AbilityCastType == ECastType::Casted_Charged)
			{
				bIsCharged = true;
				bIsOnCooldown = true;
			}
			if (AbilityCastType == ECastType::Channeled)
			{
				OnAbilityStart();
				bIsChanneled = true;
				bIsOnCooldown = true;
			}
			if (AbilityCastType == ECastType::Instant)
			{
				bIsOnCooldown = true;
			}
		}
	}
}

void AAzurukAbilityBase::InputReleased()
{
	if (AbilityCastType == ECastType::Channeled)
	{
		OnAbilityStop();
		bIsChanneled = false;
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