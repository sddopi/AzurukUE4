

#include "Azuruk.h"
#include "AzurukAICharacter.h"


AAzurukAICharacter::AAzurukAICharacter(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	AIControllerClass = AAzurukAIController::StaticClass();

	viewField = 70.0f;
}

void AAzurukAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	spawnLoc = GetActorLocation();
}


