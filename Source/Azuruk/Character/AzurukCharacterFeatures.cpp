

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
		featureMorph = outerChar->MorphAnim;
		featureTime = outerChar->maxMorphTime;
		featureMultiplier = 1.0f;
	}
}

void UAzurukCharacterFeatures::SetFeatures(USkeletalMeshComponent* PassedMesh)
{
	PassedMesh->SetSkeletalMesh(featureMesh);
	PassedMesh->SetAnimClass(featureAnimInstance);
}

UAnimMontage* UAzurukCharacterFeatures::ReturnMorphAnim()
{
	return featureMorph;
}

bool UAzurukCharacterFeatures::EqualFeatures(USkeletalMeshComponent* Mesh)
{
	return Mesh->SkeletalMesh == featureMesh || Mesh->GetAnimInstance()->GetClass() == featureAnimInstance;
}

bool UAzurukCharacterFeatures::NotNull()
{
	return featureMesh != nullptr || featureAnimInstance != nullptr || featureMorph != nullptr;
}

//////////////////////////////////////////////////////////////////////////
// Feature Time

void UAzurukCharacterFeatures::IncreaseFeatureTime()
{
	featureTime = FMath::Min(featureTime - featureMultiplier, GetMaxFeatureTime());
}

void UAzurukCharacterFeatures::DecreaseFeatureTime()
{
	featureTime = FMath::Max(featureTime - featureMultiplier, 0.0f);
}

float UAzurukCharacterFeatures::ReturnFeatureTime()
{
	return featureTime;
}

float UAzurukCharacterFeatures::GetMaxFeatureTime() const
{
	return GetClass()->GetDefaultObject<UAzurukCharacterFeatures>()->ReturnFeatureTime();
}



