

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

	UPROPERTY(transient)
	TSubobjectPtr<class UBlackboardComponent> BlackboardComp;

	UPROPERTY(transient)
	TSubobjectPtr<class UBehaviorTreeComponent> BehaviorComp;

	virtual void PostInitializeComponents() OVERRIDE;

	virtual void Possess(class APawn* InPawn) OVERRIDE;

	virtual void BeginInactiveState() OVERRIDE;

	UFUNCTION(BlueprintCallable, Category = Behavior)
	void SeeEnemy();

	void SetEnemy(class AAzurukBaseCharacter* enemyPawn);

	AAzurukAICharacter* GetAICharacter() const;


protected:

	int32 enemyKeyID,
		  destinationKeyID;

private:

	UPROPERTY()
	AAzurukAICharacter* AICharacter;

	UPROPERTY()
	AAzurukPlayerCharacter* playerCharacter;
};
