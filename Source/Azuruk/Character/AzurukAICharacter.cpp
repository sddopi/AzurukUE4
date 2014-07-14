

#include "Azuruk.h"
#include "AzurukAICharacter.h"


AAzurukAICharacter::AAzurukAICharacter(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	AIControllerClass = AAzurukAIController::StaticClass();

	wanderRadius = 500.0f;
}

void AAzurukAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	spawnLoc = GetActorLocation();
}

void AAzurukAICharacter::FaceRotation(FRotator NewRotation, float DeltaTime)
{
	FRotator CurrentRotation = FMath::RInterpTo(GetActorRotation(), NewRotation, DeltaTime, 8.0f);

	Super::FaceRotation(CurrentRotation, DeltaTime);
}


