

#pragma once

#include "AI/BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_GetRandomDestination.generated.h"

/**
 * 
 */
UCLASS()
class UBTTask_GetRandomDestination : public UBTTask_BlackboardBase
{
	GENERATED_UCLASS_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent* OwnerComp, uint8* NodeMemory) OVERRIDE;	
};
