

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

	float featureTime;

	void SetIsMorph(bool newBool, float time);

	bool IsMorph();

	bool NotNull();

private:

	bool isMorphObject;
};
