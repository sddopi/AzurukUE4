

#pragma once

#include "Abilities/AzurukProjectile.h"
#include "Abilities/AzurukVolume_VespaSlow.h"
#include "AzurukProjectile_Vespa.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class AAzurukProjectile_Vespa : public AAzurukProjectile
{
	GENERATED_UCLASS_BODY()

	/** trigger explosion */
	void Explode(const FHitResult& Impact);

protected:

	/** slowing volume */
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TSubclassOf<class AAzurukVolume_VespaSlow> SlowingVolume;
};
