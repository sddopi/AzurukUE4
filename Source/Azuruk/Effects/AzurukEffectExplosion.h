

#pragma once

#include "Azuruk.h"
#include "AzurukEffectExplosion.generated.h"

/**
 * Spawnable effect for explosion
 * Each explosion type should be defined as separate blueprint
 */
UCLASS(Abstract, Blueprintable)
class AAzurukEffectExplosion : public AAzurukEffectBase
{
	GENERATED_UCLASS_BODY()

	/** explosion FX */
	UPROPERTY(EditDefaultsOnly, Category=Effect)
	UParticleSystem* ExplosionFX;

	/** explosion light */
	UPROPERTY(VisibleDefaultsOnly, Category=Effect)
	TSubobjectPtr<UPointLightComponent> ExplosionLight;

	/** how long keep explosion light on? */
	UPROPERTY(EditDefaultsOnly, Category=Effect)
	float ExplosionLightFadeOut;

	/** explosion sound */
	UPROPERTY(EditDefaultsOnly, Category=Effect)
	USoundCue* ExplosionSound;
	
	/** explosion decals */
	UPROPERTY(EditDefaultsOnly, Category=Effect)
	struct FDecalData Decal;

	/** spawn explosion */
	virtual void BeginPlay() OVERRIDE;

	/** update fading light */
	virtual void Tick(float DeltaSeconds) OVERRIDE;

private:

	/** Point light component name */
	FName ExplosionLightComponentName;
};
