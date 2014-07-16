

#include "Azuruk.h"
#include "AzurukAIController.h"


AAzurukAIController::AAzurukAIController(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	BlackboardComp = PCIP.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackBoardComp"));

	BehaviorComp = PCIP.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));

	bWantsPlayerState = true;
	PrimaryActorTick.bCanEverTick = true;
}

void AAzurukAIController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AAzurukAIController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	AICharacter = Cast<AAzurukAICharacter>(InPawn);

	// start behavior
	if (AICharacter && AICharacter->BotBehavior)
	{
		BlackboardComp->InitializeBlackboard(AICharacter->BotBehavior->BlackboardAsset);

		targetKeyID = BlackboardComp->GetKeyID("Target");
		destKeyID = BlackboardComp->GetKeyID("Destination");

		BehaviorComp->StartTree(AICharacter->BotBehavior);
	}
}

void AAzurukAIController::SetInactive()
{
	// Stop the behaviour tree/logic
	BehaviorComp->StopTree();

	// Stop any movement we already have
	StopMovement();

	// Clear Blackboard Comp
	SetTarget(NULL);
	SetDestination(FVector(FVector::ZeroVector));
}

//////////////////////////////////////////////////////////////////////////
// Enemy and Targeting

void AAzurukAIController::SeeTarget()
{
	AAzurukBaseCharacter* targetChar = nullptr;

	for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; ++It)
	{
		AAzurukBaseCharacter* TPawn = Cast<AAzurukBaseCharacter>(*It);

		if (TPawn && TPawn->IsAlive() && TPawn != GetAICharacter()->GetBaseCharacter() &&
			GetAICharacter()->SensingComponent->SensePawn(TPawn))
		{
			targetChar = TPawn;
		}
	}
	SetTarget(targetChar);
}

void AAzurukAIController::SetTarget(AAzurukBaseCharacter* targetPawn)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(targetKeyID, targetPawn);
	}
}

void AAzurukAIController::SetDestination(FVector newDest)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsVector(destKeyID, newDest);
	}
}

AAzurukAICharacter* AAzurukAIController::GetAICharacter() const
{
	return AICharacter;
}


