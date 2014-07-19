

#pragma once

#include "AzurukAbilityProjectile.generated.h"

USTRUCT()
struct FProjectileAbilityData
{
	GENERATED_USTRUCT_BODY()

	/** projectile class */
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<class AAzurukProjectile> ProjectileClass;

	/** life time */
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	float ProjectileLife;

	/** damage at impact point */
	UPROPERTY(EditDefaultsOnly, Category = "AbilityStat")
	int32 ExplosionDamage;

	/** radius of damage */
	UPROPERTY(EditDefaultsOnly, Category = "AbilityStat")
	float ExplosionRadius;

	/** type of damage */
	UPROPERTY(EditDefaultsOnly, Category = "AbilityStat")
	TSubclassOf<UDamageType> DamageType;

	/** defaults */
	FProjectileAbilityData()
	{
		ProjectileClass = NULL;
		ProjectileLife = 10.0f;
		ExplosionDamage = 100;
		ExplosionRadius = 300.0f;
		DamageType = UDamageType::StaticClass();
	}
};

/**
 * A ability that spawns a projectile from a socket on the pawn
 */
UCLASS(BlueprintType, Blueprintable)
class AAzurukAbilityProjectile : public AAzurukAbilityBase
{
	GENERATED_UCLASS_BODY()

	/* overrides */
	void OnAbilityStart();
	void OnAbilityStop();
	void OnAbilityInitialized();

	/** apply config on projectile */
	void ApplyAbilityConfig(FProjectileAbilityData& Data);

	/** ability config */
	UPROPERTY(EditDefaultsOnly, Category = Config)
	FProjectileAbilityData ProjectileConfig;

//////////////////////////////////////////////////////////////////////////
// Ability Usage

protected:

	/** ability specific usage implementation */
	virtual void UseAbility() override;

	/** spawn projectile on server */
	UFUNCTION(reliable, server, WithValidation)
	void ServerFireProjectile(FVector Origin, FVector_NetQuantizeNormal ShootDir);

	/** Get the aim of the ability, allowing for adjustments to be made by the weapon */
	virtual FVector GetAdjustedAim() const;

	/** Get the aim of the camera */
	FVector GetCameraAim() const;

	/** get the originating location for camera damage */
	FVector GetCameraDamageStartLocation(const FVector& AimDir) const;

	/** find hit */
	FHitResult AbilityTrace(const FVector& TraceFrom, const FVector& TraceTo) const;
};
