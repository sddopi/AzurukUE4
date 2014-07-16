

#include "Azuruk.h"
#include "AzurukAICharacter.h"


AAzurukAICharacter::AAzurukAICharacter(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	AIControllerClass = AAzurukAIController::StaticClass();

	SensingComponent = PCIP.CreateDefaultSubobject<UAzurukSensingComponent>(this, TEXT("SensingComponent"));

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

void AAzurukAICharacter::Die(float KillingDamage, struct FDamageEvent const& DamageEvent, class AController* Killer, class AActor* DamageCauser)
{	
	AAzurukAIController* AC = Cast<AAzurukAIController>(GetController());

	if (AC)
	{
		AC->SetInactive();
	}
	Super::Die(KillingDamage, DamageEvent, Killer, DamageCauser);
}


