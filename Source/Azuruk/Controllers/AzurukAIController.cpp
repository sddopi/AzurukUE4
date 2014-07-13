

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

	for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; ++It)
	{
		playerCharacter = Cast<AAzurukPlayerCharacter>(*It);
	}
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
	/*FVector enemyDir = GetNavAgentLocation() - playerCharacter->GetNavAgentLocation();

	if (FRotationMatrix::MakeFromX(GetNavAgentLocation() - enemyDir).Rotator() <= AICharacter->fieldofView &&
		FVector::Dist(GetNavAgentLocation(), playerCharacter->GetNavAgentLocation()) < sightDistance)
	{
		FVector viewPoint = GetPawn()->GetPawnViewLocation();

		FHitResult hit;

		FCollisionQueryParams CollisionParams(NAME_LineOfSight, true, GetPawn());
		CollisionParams.AddIgnoredActor(playerCharacter);
	
		if (GetWorld->LineTraceSingle(hit, GetPawn()->BaseEyeHeight, playerCharacter->GetTargetLocation(GetPawn()), ECC_Visibility, CollisionParams))
		{

		}
	}*/
}

void AAzurukAIController::SetEnemy(class AAzurukBaseCharacter* enemyPawn)
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

