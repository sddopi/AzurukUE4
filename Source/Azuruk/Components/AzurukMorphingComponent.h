

#pragma once

#include "Objects/AzurukPlayerFeatures.h"
#include "AzurukMorphingComponent.generated.h"

/**
 * 
 */
UCLASS()
class UAzurukMorphingComponent : public UActorComponent
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Morphing")
	float defaultMorphTime;

	UPROPERTY(EditDefaultsOnly, Category = "Morphing")
	float morphTimeInterval;

	UPROPERTY(EditDefaultsOnly, Category = "Morphing")
	float morphTimeMultiplier;

	/* Add CharacterFeatures to a PlayerFeature Array
	 * @Param - UAzurukCharacterFeatures
	 */
	void AddMorph(UAzurukCharacterFeatures* otherFeatures);

	/*
	 *
	 */
	bool HasMorph(UAzurukCharacterFeatures* otherFeatures);

	/*
	 *
	 */
	void SetMorph(const uint8 index);

	/*
	 *
	 */
	bool CanMorph(const uint8 index);

	/* Returns the Indexed UAzurukPlayerFeatures
	 * @Param - int index
	 */
	UAzurukPlayerFeatures* ReturnMorph(const uint8 index);

	AAzurukPlayerCharacter* ReturnAzurukOwner();

private:

	virtual void PostInitProperties() override;

	virtual void BeginDestroy() override;

	class AAzurukPlayerCharacter* ownerPlayer;

	TArray< class UAzurukPlayerFeatures* > morphArray;

	uint8 currentMorph;
};
