

#include "Azuruk.h"
#include "AzurukCharacterFeatures.h"

UAzurukCharacterFeatures::UAzurukCharacterFeatures(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

void UAzurukCharacterFeatures::InitializeFeatures(USkeletalMesh* mesh, UAnimInstance* anim)
{
	charMesh = mesh;
	charAnim = anim;
}

