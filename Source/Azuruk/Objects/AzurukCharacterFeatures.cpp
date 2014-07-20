

#include "Azuruk.h"
#include "AzurukCharacterFeatures.h"

UAzurukCharacterFeatures::UAzurukCharacterFeatures(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	AAzurukBaseCharacter* outerChar = Cast<AAzurukBaseCharacter>(GetOuter());

	if (outerChar)
	{
		featureMesh = outerChar->Mesh->SkeletalMesh;
		featureAnimInstance = outerChar->Mesh->GetAnimInstance()->GetClass();
		featureMorphAnim = outerChar->morphAnim;
		featureTime = outerChar->maxMorphTime;
	}
}

void UAzurukCharacterFeatures::SetFeatures(AAzurukBaseCharacter* PassedCharacter)
{
	PassedCharacter->Mesh->SetSkeletalMesh(featureMesh);
	PassedCharacter->Mesh->SetAnimInstanceClass(featureAnimInstance);
	PassedCharacter->morphAnim = featureMorphAnim;
}

UAnimMontage* UAzurukCharacterFeatures::ReturnMorphAnim()
{
	return featureMorphAnim;
}

bool UAzurukCharacterFeatures::EqualFeatures(USkeletalMeshComponent* Mesh)
{
	return Mesh->SkeletalMesh == featureMesh || Mesh->GetAnimInstance()->GetClass() == featureAnimInstance;
}

bool UAzurukCharacterFeatures::NotNull()
{
	return featureMesh != nullptr || featureAnimInstance != nullptr || featureMorphAnim != nullptr;
}

//////////////////////////////////////////////////////////////////////////
// Feature Time

float UAzurukCharacterFeatures::ReturnFeatureTime()
{
	return featureTime;
}

float UAzurukCharacterFeatures::ReturnMaxFeatureTime() const
{
	return GetClass()->GetDefaultObject<UAzurukCharacterFeatures>()->ReturnFeatureTime();
}



