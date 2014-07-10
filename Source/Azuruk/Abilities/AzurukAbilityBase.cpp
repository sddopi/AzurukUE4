

#include "Azuruk.h"
#include "AzurukAbilityBase.h"


AAzurukAbilityBase::AAzurukAbilityBase(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	isOnCooldown = false;
	isChanneled = false;
	isCasted = false;
}

void AAzurukAbilityBase::Tick(float DeltaTime)
{
	if (isOnCooldown)
	{
		currentCooldownTime += DeltaTime;
		if (currentCooldownTime >= AbilityCooldownTime)
		{
			currentCooldownTime = 0;
			isOnCooldown = false;
		}
	}

	if (isChanneled)
	{
		currentIntervalTime += DeltaTime;
		if (currentIntervalTime >= ChannelInterval)
		{
			currentIntervalTime = 0;
			OnAbilityStart();
		}
	}

	if (isCasted)
	{
		currentCastTime += DeltaTime;
		if (currentCastTime >= MaxCastTime)
		{
			currentCastTime = 0;
			isCasted = false;
			OnAbilityStart();
		}
	}
	if (isCharged)
	{
		currentChargeTime += DeltaTime;
		if (currentChargeTime >= MaxCastTime)
		{
			currentChargeTime = 0;
			isCharged = false;
			OnAbilityStart();
		}
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
		if (!isOnCooldown)
		{
			if (AbilityCastType == ECastType::Casted)
			{
				isCasted = true;
				isOnCooldown = true;
			}
			if (AbilityCastType == ECastType::Casted_Charged)
			{
				isCharged = true;
				isOnCooldown = true;
			}
			if (AbilityCastType == ECastType::Channeled)
			{
				OnAbilityStart();
				isChanneled = true;
				isOnCooldown = true;
			}
		}
	}
}

void AAzurukAbilityBase::InputReleased()
{
	if (AbilityCastType == ECastType::Channeled)
	{
		OnAbilityStop();
		isChanneled = false;
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