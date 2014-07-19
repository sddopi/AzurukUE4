

#pragma once

#include "Classes/AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
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

	virtual void PostInitializeComponents() override;

	virtual void Possess(class APawn* InPawn) override;

	virtual void SetInactive();

//////////////////////////////////////////////////////////////////////////
// Enemy and Targeting

	UFUNCTION(BlueprintCallable, Category = Behavior)
	void SeeTarget();

	void SetTarget(AAzurukBaseCharacter* targetPawn);

	void SetDestination(FVector newDest);

//////////////////////////////////////////////////////////////////////////
// 

	AAzurukAICharacter* GetAICharacter() const;

protected:

	int32 targetKeyID,
		  destKeyID;

private:

	UPROPERTY()
	AAzurukAICharacter* AICharacter;
};
