

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
	void SetFeatures(AAzurukBaseCharacter* PassedCharacter);

	/* Checks if passed features are the same as current */
	bool EqualFeatures(USkeletalMeshComponent* Mesh);

	/* Checks if feature is null */
	bool NotNull();

	/*  */
	UAnimMontage* ReturnMorphAnim();

//////////////////////////////////////////////////////////////////////////
// Feature Time

	/* Return Morph Time */
	float ReturnFeatureTime();

	/* Returns Max Morph Time */
	float ReturnMaxFeatureTime() const;

protected:

	UPROPERTY()
	USkeletalMesh* featureMesh;

	UPROPERTY()
	UClass* featureAnimInstance;

	UPROPERTY()
	UAnimMontage* featureMorphAnim;

	UPROPERTY()
	float featureTime;
};
