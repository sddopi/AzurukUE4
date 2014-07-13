

#include "Azuruk.h"
#include "BTTask_GetRandomDestination.h"


UBTTask_GetRandomDestination::UBTTask_GetRandomDestination(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
}

EBTNodeResult::Type UBTTask_GetRandomDestination::ExecuteTask(UBehaviorTreeComponent* OwnerComp, uint8* NodeMemory)
{

	UBehaviorTreeComponent* MyComp = OwnerComp;
	AAzurukAIController* MyController = MyComp ? Cast<AAzurukAIController>(MyComp->GetOwner()) : NULL;

	if (MyController == NULL)
	{
		return EBTNodeResult::Failed;
	}

	AAzurukAICharacter* AIChar = MyController->GetAICharacter();

	if (AIChar)
	{
		FNavLocation navDest;
		const FVector Loc = GetWorld()->GetNavigationSystem()->GetRandomPointInRadius(MyController, AIChar->spawnLoc, AIChar->wanderRadius);
		if (Loc != FVector::ZeroVector)
		{
			MyComp->GetBlackboardComponent()->SetValueAsVector(BlackboardKey.GetSelectedKeyID(), Loc);
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}


