

#pragma once

#include "GameFramework/AIController.h"
#include "AzurukAIController.generated.h"

/**
 * 
 */
UCLASS()
class AAzurukAIController : public AAIController
{
	GENERATED_UCLASS_BODY()

	virtual void PostInitializeComponents() OVERRIDE;

private:

	UPROPERTY()
	FVector SpawnLoc;
	
};
