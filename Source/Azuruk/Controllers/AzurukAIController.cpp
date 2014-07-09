

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

	SpawnLoc = this->GetNavAgentLocation();

	/*UNavigationSystem::GetRandomPointInRadius()*/
}

void AAzurukAIController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	AAzurukAICharacter* AIChar = Cast<AAzurukAICharacter>(InPawn);

	// start behavior
	if (AIChar && AIChar->BotBehavior)
	{
		BlackboardComp->InitializeBlackboard(AIChar->BotBehavior->BlackboardAsset);

		BehaviorComp->StartTree(AIChar->BotBehavior);
	}
}

void AAzurukAIController::BeginInactiveState()
{
	Super::BeginInactiveState();
}

