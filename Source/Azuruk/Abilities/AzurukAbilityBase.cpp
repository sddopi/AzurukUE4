

#include "Azuruk.h"
#include "AzurukAbilityBase.h"


UAzurukAbilityBase::UAzurukAbilityBase(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	isOnCooldown = false;
	isChanneled = false;
	isCasted = false;
}

void UAzurukAbilityBase::Tick(float DeltaTime)
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

bool UAzurukAbilityBase::IsTickable() const
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

UWorld* UAzurukAbilityBase::GetWorld() const
{
	if (!AbilityOwner)
		return NULL;
	UWorld* const World = GEngine->GetWorldFromContextObject(AbilityOwner);
	return World ? World : nullptr;
}

void UAzurukAbilityBase::Initialize(APawn* owner, AController* instigator)
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

void UAzurukAbilityBase::InputPressed()
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

void UAzurukAbilityBase::InputReleased()
{
	if (AbilityCastType == ECastType::Channeled)
	{
		OnAbilityStop();
		isChanneled = false;
	}
}