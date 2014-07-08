

#include "Azuruk.h"
#include "AzurukCharacterFeatures.h"

UAzurukCharacterFeatures::UAzurukCharacterFeatures(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	featureMesh = nullptr;
	featureAnimInstance = nullptr;
	morphTime = 100.0f;
}

void UAzurukCharacterFeatures::InitFeatures(USkeletalMesh* Mesh, UClass* AnimInstance)
{
	featureMesh = Mesh;
	featureAnimInstance = AnimInstance;
}

void UAzurukCharacterFeatures::SetFeatures(USkeletalMeshComponent* PassedMesh)
{
	if (this->NotNull() && morphTime > 0.0f)
	{
		PassedMesh->SetAnimClass(featureAnimInstance);
		PassedMesh->SetSkeletalMesh(featureMesh);

	}
}

bool UAzurukCharacterFeatures::EqualFeatures(USkeletalMeshComponent* Mesh)
{
	return Mesh->SkeletalMesh == featureMesh || Mesh->GetAnimInstance()->GetClass() == featureAnimInstance;
}

bool UAzurukCharacterFeatures::NotNull()
{
	return featureMesh != nullptr || featureAnimInstance != nullptr;
}


