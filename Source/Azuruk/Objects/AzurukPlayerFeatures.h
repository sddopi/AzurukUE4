

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

	UPROPERTY()
	bool morphActive;

	void SetMorphFeatures(UAzurukCharacterFeatures* otherFeatures);

	void PassCharacterFeatures(class AAzurukPlayerCharacter* MorphOwner);

	void SetMorphTimer(class AAzurukPlayerCharacter* MorphOwner, float TimerInterval);

	void ModifyMorphTime();

	float ReturnMorphPercent();

	friend bool operator==(UAzurukPlayerFeatures& LHS, UAzurukCharacterFeatures& RHS);

	UAzurukPlayerFeatures& operator=(UAzurukCharacterFeatures& other);

private:

	UPROPERTY()
	float maxmorphTime;
	
	UPROPERTY()
	float morphTime;

	UPROPERTY()
	float morphTimeMultiplier;

	UPROPERTY()
	class UAzurukMorphingComponent* OwnerComp;

	UPROPERTY()
	USkeletalMesh* morphSkelMesh;

	UPROPERTY()
	UClass* morphAnimInstance;

	UPROPERTY()
	UAnimMontage* morphMorphAnim;
};
