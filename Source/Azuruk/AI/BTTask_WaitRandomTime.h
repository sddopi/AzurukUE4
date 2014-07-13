

#pragma once

#include "AI/BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_WaitRandomTime.generated.h"

/**
 * 
 */
UCLASS()
class UBTTask_WaitRandomTime : public UBTTaskNode
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(Category=Node, EditAnywhere)
	float WaitTimeMin;

	UPROPERTY(Category=Node, EditAnywhere)
	float WaitTimeMax;

	UPROPERTY()
	float WaitTime;

	virtual EBTNodeResult::Type ExecuteTask(class UBehaviorTreeComponent* OwnerComp, uint8* NodeMemory) OVERRIDE;
	virtual uint16 GetInstanceMemorySize() const OVERRIDE;
	virtual void DescribeRuntimeValues(const class UBehaviorTreeComponent* OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const OVERRIDE;
	virtual FString GetStaticDescription() const OVERRIDE;

protected:

	virtual void TickTask(class UBehaviorTreeComponent* OwnerComp, uint8* NodeMemory, float DeltaSeconds) OVERRIDE;	
};
