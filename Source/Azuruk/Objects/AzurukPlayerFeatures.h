

#pragma once

#include "AzurukPlayerFeatures.generated.h"

/**
 * 
 */
UCLASS()
class UAzurukPlayerFeatures : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	void SetMorphFeatures(UAzurukCharacterFeatures* otherFeatures);

	void PassCharacterFeatures(class AAzurukPlayerCharacter* MorphOwner);

	void SetMorphTimer(class AAzurukPlayerCharacter* MorphOwner, float TimerInterval, bool Active);

	void ModifyMorphTime();

	float ReturnMorphPercent();

	friend bool operator==(UAzurukPlayerFeatures& LHS, UAzurukCharacterFeatures& RHS);

	UAzurukPlayerFeatures& operator=(UAzurukCharacterFeatures& other);

private:

	UPROPERTY()
	float maxmorphTime;
	
	UPROPERTY()
	float morphTime;

	USkeletalMesh* morphSkelMesh;

	UClass* morphAnimInstance;

	UAnimMontage* morphMorphAnim;

};
