

#pragma once

#include "Object.h"
#include "AzurukCharacterFeatures.generated.h"

/**
 * 
 */
UCLASS()
class UAzurukCharacterFeatures : public UObject
{
	GENERATED_UCLASS_BODY()

//////////////////////////////////////////////////////////////////////////
// Features

	/* */
	void SetFeatures(USkeletalMeshComponent* PassedMesh);

	/* Checks if passed features are the same as current */
	bool EqualFeatures(USkeletalMeshComponent* Mesh);

	/* Checks if feature is null */
	bool NotNull();

	/*  */
	UAnimMontage* ReturnMorphAnim();

//////////////////////////////////////////////////////////////////////////
// Feature Time

	/*  */
	void IncreaseFeatureTime();

	/*  */
	void DecreaseFeatureTime();

	/* Return Morph Time */
	float ReturnFeatureTime();

	/* Returns Max Morph Time */
	float GetMaxFeatureTime() const;

protected:

	UPROPERTY()
	USkeletalMesh* featureMesh;

	UPROPERTY()
	UClass* featureAnimInstance;

	UPROPERTY()
	UAnimMontage* featureMorph;

	UPROPERTY()
	float featureTime;

	UPROPERTY()
	float featureMultiplier;
};
