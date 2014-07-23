

#include "Azuruk.h"
#include "AzurukVolume_VespaSlow.h"


AAzurukVolume_VespaSlow::AAzurukVolume_VespaSlow(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	bWaterVolume = true;
	FluidFriction = 100.f;
	CurrentSpawnTime = 0.f;

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bAllowTickOnDedicatedServer = true;
}

void AAzurukVolume_VespaSlow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentSpawnTime += DeltaTime;

	if (CurrentSpawnTime >= SlowDuration)
	{
		bWaterVolume = false;
		Destroy();
	}
}
