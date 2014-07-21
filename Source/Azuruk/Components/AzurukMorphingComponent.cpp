

#include "Azuruk.h"
#include "AzurukMorphingComponent.h"


UAzurukMorphingComponent::UAzurukMorphingComponent(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	morphTimeMultiplier = 1.f;
	morphTimeInterval = 1.f;
	morphTimeMax = 100.f;
	currentMorph = 0;
}

void UAzurukMorphingComponent::AddMorph(UAzurukCharacterFeatures* newMorph)
{
	if (newMorph->NotNull())
	{
		newMorph->SetIsMorph(true, morphTimeMax);
		morphArray.Add(newMorph);
	}
}

bool UAzurukMorphingComponent::ContainsMorph(UAzurukCharacterFeatures* newMorph)
{
	return morphArray.Contains(newMorph);
}

bool UAzurukMorphingComponent::IsValid(const uint8 index)
{
	return morphArray.IsValidIndex(index);
}

void UAzurukMorphingComponent::SetMorph(const uint8 index)
{
	AAzurukPlayerCharacter* ownerCharacter = Cast<AAzurukPlayerCharacter>(GetOwner());

	ownerCharacter->Mesh->SetSkeletalMesh(morphArray[index]->featureSkelMesh);
	ownerCharacter->Mesh->SetAnimInstanceClass(morphArray[index]->featureAnimInstance);
	ownerCharacter->morphAnim = morphArray[index]->featureMorphAnim;
	currentMorph = index;
}

bool UAzurukMorphingComponent::CanMorph(const uint8 index)
{
	AAzurukPlayerCharacter* ownerCharacter = Cast<AAzurukPlayerCharacter>(GetOwner());

	return morphArray.IsValidIndex(index) &&
		morphArray[index]->featureTime != 0.f &&
		ownerCharacter->InIdleStates();
}

bool UAzurukMorphingComponent::IsDefaultMorph()
{
	return currentMorph == EFeatureName::FeatureDefault;
}

float UAzurukMorphingComponent::GetMorphPercent(const uint8 index) const
{
	if (morphArray.IsValidIndex(index))
	{
		return morphArray[index]->featureTime / morphTimeMax;
	}
	return 0.f;
}

void UAzurukMorphingComponent::BeginDestroy()
{
	Super::BeginDestroy();
}



