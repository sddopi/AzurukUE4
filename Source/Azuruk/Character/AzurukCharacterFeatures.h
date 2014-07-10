

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

	/* Sets the SkelMesh & AnimInstance on Passed Mesh */
	void SetFeatures(USkeletalMeshComponent* PassedMesh);

	/* Checks if passed features are the same as current */
	bool EqualFeatures(USkeletalMeshComponent* Mesh);

	/* Checks if feature is null */
	bool NotNull();

	/* Return Morph Time */
	float ReturnFeatureTime();

	/* Returns Max Morph Time */
	float ReturnMaxFeatureTime() const;

	/*  */
	void ModifyFeatureTime();

	/* */
	bool isFeatureActive();

	/* */
	bool isFeatureDepleted();

	/* */
	void ModifyFeatureActive(bool newBool);

protected:

	UPROPERTY()
	USkeletalMesh* featureMesh;

	UPROPERTY()
	UClass* featureAnimInstance;

	UPROPERTY(EditDefaultsOnly, Category = "Character Features")
	float featureTime;

	UPROPERTY()
	bool featureActive;
};
