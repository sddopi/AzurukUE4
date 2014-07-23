

#include "Azuruk.h"
#include "AzurukMorphingComponent.h"


UAzurukMorphingComponent::UAzurukMorphingComponent(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	defaultMorphTime = 100.f;
	morphTimeInterval = 1.f;
	morphTimeMultiplier = 1.f;
	currentMorph = 0;
}

void UAzurukMorphingComponent::PostInitProperties()
{
	Super::PostInitProperties();
	// Set Owner as Player
	ownerPlayer = Cast<AAzurukPlayerCharacter>(GetOwner());
}

void UAzurukMorphingComponent::BeginDestroy()
{
	Super::BeginDestroy();
	// Empty the TArray
	morphArray.Empty();
}

void UAzurukMorphingComponent::AddMorph(UAzurukCharacterFeatures* otherFeatures)
{
	UAzurukPlayerFeatures* playerMorph = NewObject<UAzurukPlayerFeatures>(this);
	// Pass Over Features to Morph
	*playerMorph = *otherFeatures;
	// Add to Array
	morphArray.Add(playerMorph);
}

bool UAzurukMorphingComponent::HasMorph(UAzurukCharacterFeatures* otherFeatures)
{
	for (UAzurukPlayerFeatures* iFeature : morphArray)
	{
		if (*iFeature == *otherFeatures)
		{
			return true;
		}
	}
	return false;
}

void UAzurukMorphingComponent::SetMorph(const uint8 index)
{
	if (currentMorph != EFeatureName::FeatureDefault)
	{
		morphArray[currentMorph]->morphActive = false;
	}

	if (index != EFeatureName::FeatureDefault)
	{
		morphArray[index]->morphActive = true;
		morphArray[index]->SetMorphTimer(ownerPlayer, morphTimeInterval);
	}
	
	morphArray[index]->PassCharacterFeatures(ownerPlayer);
	
	currentMorph = index;
}

bool UAzurukMorphingComponent::CanMorph(const uint8 index)
{
	if (morphArray.IsValidIndex(index))
	{
		if (morphArray[index]->ReturnMorphPercent() != 0.f)
		{
			return true;
		}
	}
	return false;
}

UAzurukPlayerFeatures* UAzurukMorphingComponent::ReturnMorph(const uint8 index)
{
	if (morphArray.IsValidIndex(index))
	{
		return morphArray[index];
	}
	return nullptr;
}

AAzurukPlayerCharacter* UAzurukMorphingComponent::ReturnAzurukOwner()
{
	return ownerPlayer;
}





