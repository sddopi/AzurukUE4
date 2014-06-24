

#include "Azuruk.h"
#include "AzurukBaseCharacter.h"

const uint8 DEFAULTFEATURE = uint8(0);

AAzurukBaseCharacter::AAzurukBaseCharacter(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// Don't let Azuruk Characters die
	InitialLifeSpan = 0;

	// Rotate Mesh
	Mesh->SetRelativeRotation(FRotator(0, 0, -90));

	// Configure character movement
	CharacterMovement->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	CharacterMovement->RotationRate = FRotator(0.0f, 560.0f, 0.0f); // ...at this rotation rate
	CharacterMovement->JumpZVelocity = 600.f;
	CharacterMovement->AirControl = 0.2f;
}




