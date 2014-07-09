

#include "Azuruk.h"
#include "AzurukAIController.h"


AAzurukAIController::AAzurukAIController(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
}

void AAzurukAIController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SpawnLoc = this->GetNavAgentLocation();
}


