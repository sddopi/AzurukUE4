

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
		featureTime = outerChar->maxMorphTime;
		featureActive = false;
	}
}

void UAzurukCharacterFeatures::SetFeatures(USkeletalMeshComponent* PassedMesh)
{
	PassedMesh->SetAnimClass(featureAnimInstance);
	PassedMesh->SetSkeletalMesh(featureMesh);
}

bool UAzurukCharacterFeatures::EqualFeatures(USkeletalMeshComponent* Mesh)
{
	return Mesh->SkeletalMesh == featureMesh || Mesh->GetAnimInstance()->GetClass() == featureAnimInstance;
}

bool UAzurukCharacterFeatures::NotNull()
{
	return featureMesh != nullptr || featureAnimInstance != nullptr;
}

float UAzurukCharacterFeatures::ReturnFeatureTime()
{
	return featureTime;
}

float UAzurukCharacterFeatures::ReturnMaxFeatureTime() const
{
	return GetClass()->GetDefaultObject<UAzurukCharacterFeatures>()->ReturnFeatureTime();
}

void UAzurukCharacterFeatures::ModifyFeatureTime()
{
	if (featureActive)
	{
		featureTime = FMath::Max(featureTime - 1.0f, 0.0f);
	}
	else
	{
		featureTime = FMath::Min(featureTime + 1.0f, ReturnMaxFeatureTime());
	}
}

bool UAzurukCharacterFeatures::isFeatureActive()
{
	return featureActive;
}

bool UAzurukCharacterFeatures::isFeatureDepleted()
{
	return featureTime == 0.0f;
}

void UAzurukCharacterFeatures::ModifyFeatureActive(bool newBool)
{
	featureActive = newBool;
}

