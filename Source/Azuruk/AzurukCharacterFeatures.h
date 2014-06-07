#pragma once

#include "Object.h"
#include "Components/SkeletalMeshComponent.h"
#include "AzurukCharacterFeatures.generated.h"

/**
 * 
 */
UCLASS()
class UAzurukCharacterFeatures : public UObject
{
	GENERATED_UCLASS_BODY()

	/* Name of Feature */
	UPROPERTY()
	FName charName;
	/* Mesh of Feature */
	UPROPERTY()
	TSubobjectPtr<USkeletalMeshComponent> charMesh;

public:

	void IntializeFeatures(FName, USkeletalMeshComponent)
	{

	}
};
