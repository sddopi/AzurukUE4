

#pragma once

#include "Object.h"
#include "AzurukAbilityBase.h"
#include "AzurukAbilityTest.generated.h"

/**
 * Test ability
 */
UCLASS(BlueprintType, Blueprintable)
class AAzurukAbilityTest : public AAzurukAbilityBase
{
	GENERATED_UCLASS_BODY()

	/* Overrides */
	virtual void Tick(float DeltaTime)  OVERRIDE;

	virtual void InputPressed() OVERRIDE;
	virtual void InputReleased() OVERRIDE;
protected:
	virtual void Initialize(APawn* owner, APawn* instigator) OVERRIDE;


//////////////////////////////////////////////////////////////////////////
// Projectile Functions
public:

	UFUNCTION(BlueprintCallable, Category = "Ability|Helpers")
	FHitResult GetHitResult(float Range, FName StartSocket);

	UFUNCTION(BlueprintCallable, Category = "Ability|Helpers")
	AActor* GetActorHit(float Range, FName StartSocket);

	UFUNCTION(BlueprintCallable, Category = "Ability|Helpers")
	void SpawnTrailEffect(UParticleSystem* trailFX, float trailSpeed, FName trailSpeedParam, FHitResult target, FName SocketName);

protected:
	UFUNCTION(BlueprintCallable, Category = "Ability|Helpers")
	FVector GetCameraAim() const;

private:
	FHitResult RangedPowerTrace(const FVector& StartTrace, const FVector& EndTrace) const;
	FVector GetCameraDamageStarLocation(const FVector& AimDir) const;
	FVector GetCastingLocation(FName SocketName) const;

};
