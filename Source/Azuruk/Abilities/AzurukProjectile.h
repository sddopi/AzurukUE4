

#pragma once

#include "AzurukAbilityProjectile.h"
#include "Effects/AzurukEffectExplosion.h"
#include "AzurukProjectile.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable, DependsOn = AAzurukAbilityProjectile)
class AAzurukProjectile : public AActor
{
	GENERATED_UCLASS_BODY()

	/** initial setup */
	virtual void PostInitializeComponents() OVERRIDE;

	/** setup velocity */
	void InitVelocity(FVector& ShootDirection);

	/** handle hit */
	UFUNCTION()
	void OnImpact(const FHitResult& HitResult);

protected:

	/** movement component */
	UPROPERTY(VisibleDefaultsOnly, Category = "Projectile")
	TSubobjectPtr<UProjectileMovementComponent> MovementComp;

	/** collisions */
	UPROPERTY(VisibleDefaultsOnly, Category = "Projectile")
	TSubobjectPtr<USphereComponent> CollisionComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Projectile")
	TSubobjectPtr<UParticleSystemComponent> ParticleComp;

	/** effects for explosion */
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TSubclassOf<class AAzurukEffectExplosion> ExplosionTemplate;

	/** controller that fired me (cache for damage calculations) */
	TWeakObjectPtr<AController> MyController;

	/** projectile data */
	struct FProjectileAbilityData AbilityConfig;

	/** did it explode? */
	UPROPERTY(Transient, ReplicatedUsing = OnRep_Exploded)
	bool bExploded;

	/** [client] explosion happened */
	UFUNCTION()
	void OnRep_Exploded();

	/** trigger explosion */
	void Explode(const FHitResult& Impact);

	/** shutdown projectile and prepare for destruction */
	void DisableAndDestroy();

	/** update velocity on client */
	virtual void PostNetReceiveVelocity(const FVector& NewVelocity) OVERRIDE;
};
