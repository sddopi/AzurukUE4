

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

		enemyKeyID = BlackboardComp->GetKeyID("Enemy");

		BehaviorComp->StartTree(AICharacter->BotBehavior);
	}
}

void AAzurukAIController::BeginInactiveState()
{
	Super::BeginInactiveState();
}

void AAzurukAIController::SeeEnemy()
{	
}

void AAzurukAIController::SetEnemy(class APawn* enemyPawn)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(enemyKeyID, enemyPawn);
	}
}

AAzurukAICharacter* AAzurukAIController::GetAICharacter() const
{
	return AICharacter;
}

AAzurukPlayerCharacter* AAzurukAIController::GetPlayerCharacter() const
{
	APlayerController* PlayerController = NULL;

	if (GetWorld()->GetPlayerControllerIterator())
	{
		PlayerController = *(GetWorld()->GetPlayerControllerIterator());
		return Cast<AAzurukPlayerCharacter>(PlayerController->GetPawn());
	}
	return nullptr;
}


