

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

	virtual void PostInitializeComponents() OVERRIDE;

	UPROPERTY(EditAnywhere, Category=Behavior)
	class UBehaviorTree* BotBehavior;

	UPROPERTY(EditDefaultsOnly, Category = "AI Properties")
	float viewField;

	UPROPERTY()
	FVector spawnLoc;
};
