

#include "Azuruk.h"
#include "AzurukCharacterFeatures.h"

UAzurukCharacterFeatures::UAzurukCharacterFeatures(USkeletalMesh* SkelMesh, UClass* AnimInstance, UAnimMontage* MorphAnim)
{
	featureSkelMesh = SkelMesh;
	featureAnimInstance = AnimInstance;
	featureMorphAnim = MorphAnim;
	featureTime = 0.f;
	isMorphObject = false;
}

UAzurukCharacterFeatures::~UAzurukCharacterFeatures()
{
}

void UAzurukCharacterFeatures::SetIsMorph(bool newBool, float time)
{
	isMorphObject = newBool;
	featureTime = time;
}

bool UAzurukCharacterFeatures::IsMorph()
{
	return isMorphObject;
}

bool UAzurukCharacterFeatures::NotNull()
{
	return featureSkelMesh != nullptr &&
		   featureAnimInstance != nullptr &&
		   featureMorphAnim != nullptr;
}
