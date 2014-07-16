

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

		BehaviorComp->StartTree(AICharacter->BotBehavior);
	}
}

void AAzurukAIController::BeginInactiveState()
{
	Super::BeginInactiveState();
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

AAzurukAICharacter* AAzurukAIController::GetAICharacter() const
{
	return AICharacter;
}


