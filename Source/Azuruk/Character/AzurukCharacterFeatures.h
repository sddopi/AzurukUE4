

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
	
	/* Initialises the Feature Set */
	void InitFeatures(USkeletalMesh* Mesh, UClass* AnimInstance);

	/* Sets the SkelMesh & AnimInstance on Passed Mesh */
	void SetFeatures(USkeletalMeshComponent* PassedMesh);

	/* Checks if passed features are the same as current */
	bool EqualFeatures(USkeletalMeshComponent* Mesh);

	/* Checks if feature is null */
	bool NotNull();

private:

	UPROPERTY()
	USkeletalMesh* featureMesh;

	UPROPERTY()
	UClass* featureAnimInstance;

	UPROPERTY()
	float morphTime;
	
};
