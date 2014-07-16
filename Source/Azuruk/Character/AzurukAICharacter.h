

#pragma once

#include "Character/AzurukBaseCharacter.h"
#include "Components/AzurukSensingComponent.h"
#include "AzurukAICharacter.generated.h"

/**
 * 
 */
UCLASS()
class AAzurukAICharacter : public AAzurukBaseCharacter
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AI)
	TSubobjectPtr<class UAzurukSensingComponent> SensingComponent;

	UPROPERTY(EditAnywhere, Category=Behavior)
	class UBehaviorTree* BotBehavior;

	UPROPERTY()
	FVector spawnLoc;

	UPROPERTY(EditDefaultsOnly, Category = AI)
	float wanderRadius;

	virtual void PostInitializeComponents() OVERRIDE;

	virtual void FaceRotation(FRotator NewRotation, float DeltaTime = 0.f) OVERRIDE;

private:

	UPROPERTY()
	float visionAngleCos;
};
