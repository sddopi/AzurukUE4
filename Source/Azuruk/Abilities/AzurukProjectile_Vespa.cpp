

#include "Azuruk.h"
#include "AzurukProjectile_Vespa.h"


AAzurukProjectile_Vespa::AAzurukProjectile_Vespa(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
}

void AAzurukProjectile_Vespa::Explode(const FHitResult& Impact)
{
	Super::Explode(Impact);

	// effects and damage origin shouldn't be placed inside mesh at impact point
	const FVector NudgedImpactLocation = Impact.ImpactPoint + Impact.ImpactNormal * 10.0f;

	if (SlowingVolume) 
	{
		const FRotator SpawnRotation = Impact.ImpactNormal.Rotation();
		
		GetWorld()->SpawnActorDeferred<AAzurukVolume_VespaSlow>(SlowingVolume, NudgedImpactLocation, SpawnRotation);
	}
}