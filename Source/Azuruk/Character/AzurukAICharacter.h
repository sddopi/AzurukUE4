

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

public:

	UPROPERTY()
	FVector spawnLoc;

	UPROPERTY(EditDefaultsOnly, Category = "Azuruk|AI")
	float wanderRadius;

	virtual void PostInitializeComponents() OVERRIDE;

	virtual void FaceRotation(FRotator NewRotation, float DeltaTime = 0.f) OVERRIDE;

	/*
	* Kills pawn.
	*
	* OVERRIDE - Deactivate Behaviour
	*/
	virtual void Die(float KillingDamage, struct FDamageEvent const& DamageEvent, class AController* Killer, class AActor* DamageCauser);

private:

	UPROPERTY()
	float visionAngleCos;
};
