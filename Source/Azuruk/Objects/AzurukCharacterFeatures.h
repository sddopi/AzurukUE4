

#pragma once

/**
 * 
 */
class AZURUK_API UAzurukCharacterFeatures
{
public:

	UAzurukCharacterFeatures(USkeletalMesh* SkelMesh, UClass* AnimInstance, UAnimMontage* MorphAnim);

	~UAzurukCharacterFeatures();

	USkeletalMesh* featureSkelMesh;

	UClass* featureAnimInstance;

	UAnimMontage* featureMorphAnim;
};
