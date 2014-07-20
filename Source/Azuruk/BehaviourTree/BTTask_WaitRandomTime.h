

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_WaitRandomTime.generated.h"

struct FBTWaitTaskMemory
{
	/** time left */
	float RemainingWaitTime;
};

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

	virtual EBTNodeResult::Type ExecuteTask(class UBehaviorTreeComponent* OwnerComp, uint8* NodeMemory) override;
	virtual uint16 GetInstanceMemorySize() const override;
	virtual void DescribeRuntimeValues(const class UBehaviorTreeComponent* OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;
	virtual FString GetStaticDescription() const override;

protected:

	virtual void TickTask(class UBehaviorTreeComponent* OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;	
};
