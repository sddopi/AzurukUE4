

#pragma once

#include "GameFramework/PhysicsVolume.h"
#include "AzurukVolume_VespaSlow.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class AAzurukVolume_VespaSlow : public APhysicsVolume
{
	GENERATED_UCLASS_BODY()

	/** tick event */
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Properties")
	float SlowDuration;

private:
	float CurrentSpawnTime;
};
