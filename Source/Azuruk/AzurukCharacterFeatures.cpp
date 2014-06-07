#include "Azuruk.h"
#include "AzurukCharacterFeatures.h"


UAzurukCharacterFeatures::UAzurukCharacterFeatures(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	charMesh = PCIP.CreateDefaultSubobject<USkeletalMeshComponent> (this, TEXT("InitMesh"));

}


