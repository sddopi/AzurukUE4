

#include "Azuruk.h"
#include "BTTask_WaitRandomTime.h"


UBTTask_WaitRandomTime::UBTTask_WaitRandomTime(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	NodeName = "WaitRandomTime";
	WaitTimeMin = 0.0f;
	WaitTimeMax = 0.0f;
	
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_WaitRandomTime::ExecuteTask(class UBehaviorTreeComponent* OwnerComp, uint8* NodeMemory)
{
	WaitTime = FMath::FRandRange(WaitTimeMin, WaitTimeMax);
	FBTWaitTaskMemory* MyMemory = (FBTWaitTaskMemory*)NodeMemory;
	MyMemory->RemainingWaitTime = WaitTime;

	return EBTNodeResult::InProgress;
}

uint16 UBTTask_WaitRandomTime::GetInstanceMemorySize() const
{
	return sizeof(FBTWaitTaskMemory);
}

void UBTTask_WaitRandomTime::DescribeRuntimeValues(const class UBehaviorTreeComponent* OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const
{
	Super::DescribeRuntimeValues(OwnerComp, NodeMemory, Verbosity, Values);

	FBTWaitTaskMemory* MyMemory = (FBTWaitTaskMemory*)NodeMemory;
	if (MyMemory->RemainingWaitTime)
	{
		Values.Add(FString::Printf(TEXT("remaining: %ss"), *FString::SanitizeFloat(MyMemory->RemainingWaitTime)));
	}
}

FString UBTTask_WaitRandomTime::GetStaticDescription() const
{
	return FString::Printf(TEXT("%s: %.1fs"), *Super::GetStaticDescription(), WaitTime);
}

void UBTTask_WaitRandomTime::TickTask(class UBehaviorTreeComponent* OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FBTWaitTaskMemory* MyMemory = (FBTWaitTaskMemory*)NodeMemory;
	MyMemory->RemainingWaitTime -= DeltaSeconds;

	if (MyMemory->RemainingWaitTime <= 0.0f)
	{
		// continue execution from this node
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}


