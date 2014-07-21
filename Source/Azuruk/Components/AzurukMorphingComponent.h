

#pragma once

#include "Objects/AzurukCharacterFeatures.h"
#include "AzurukMorphingComponent.generated.h"

/**
 * 
 */
UCLASS()
class UAzurukMorphingComponent : public UActorComponent
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Morphing")
	float morphTimeMax;

	UPROPERTY(EditDefaultsOnly, Category = "Morphing")
	float morphTimeInterval;

	UPROPERTY(EditDefaultsOnly, Category = "Morphing")
	float morphTimeMultiplier;

	void AddMorph(UAzurukCharacterFeatures* newMorph);

	bool ContainsMorph(UAzurukCharacterFeatures* newMorph);

	bool IsValid(const uint8 index);

	void SetMorph(const uint8 index);

	void SetFeatures(const uint8 index);

	bool CanMorph(const uint8 index);

	bool IsDefaultMorph();

	float GetMorphPercent(const uint8 index) const;

private:

	virtual void BeginDestroy() override;

	TArray<UAzurukCharacterFeatures*> morphArray;

	uint8 currentMorph;
	
};
