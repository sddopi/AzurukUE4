

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

	virtual void FaceRotation(FRotator NewRotation, float DeltaTime = 0.f) OVERRIDE;

	UPROPERTY(EditAnywhere, Category=Behavior)
	class UBehaviorTree* BotBehavior;

	UPROPERTY(EditDefaultsOnly, Category = "AI Properties")
	float viewField;

	UPROPERTY(EditDefaultsOnly, Category = "AI Properties")
	float viewDistance;

	UPROPERTY(EditDefaultsOnly, Category = "AI Properties")
	float wanderRadius;

	UPROPERTY()
	FVector spawnLoc;
};
