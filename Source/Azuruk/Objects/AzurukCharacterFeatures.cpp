

#include "Azuruk.h"
#include "AzurukCharacterFeatures.h"

UAzurukCharacterFeatures::UAzurukCharacterFeatures(USkeletalMesh* SkelMesh, UClass* AnimInstance, UAnimMontage* MorphAnim)
{
	featureSkelMesh = SkelMesh;
	featureAnimInstance = AnimInstance;
	featureMorphAnim = MorphAnim;
}

UAzurukCharacterFeatures::~UAzurukCharacterFeatures()
{
	featureSkelMesh = nullptr;
	featureAnimInstance = nullptr;
	featureMorphAnim = nullptr;
}