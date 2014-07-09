

#pragma once

#include "Character/AzurukBaseCharacter.h"
#include "AzurukAICharacter.generated.h"

/**
 * 
 */
UCLASS()
class AAzurukAICharacter : public AAzurukBaseCharacter
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere, Category=Behavior)
	class UBehaviorTree* BotBehavior;
	
};
