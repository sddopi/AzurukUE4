

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

	void InitializeFeatures(USkeletalMesh*, UAnimInstance*);

	UPROPERTY()
	class USkeletalMesh* charMesh;

	UPROPERTY()
	class UAnimInstance* charAnim;
};
