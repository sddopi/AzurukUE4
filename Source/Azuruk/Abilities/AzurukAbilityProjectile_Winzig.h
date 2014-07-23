

#pragma once

#include "Abilities/AzurukAbilityProjectile.h"
#include "AzurukAbilityProjectile_Winzig.generated.h"

USTRUCT()
struct FHitData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	FVector HitLocation;

	UPROPERTY()
	bool bCanWinzigUse;

	UPROPERTY()
	FHitResult HitResult;

	/** defaults */
	FHitData()
	{
		//HitResult = new FHitResult(ForceInit);
		HitLocation = FVector(0, 0, 0);
		bCanWinzigUse = false;
	}
};

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class AAzurukAbilityProjectile_Winzig : public AAzurukAbilityProjectile
{
	GENERATED_UCLASS_BODY()
	
//////////////////////////////////////////////////////////////////////////
// Ability Usage

protected:

	/** ability specific usage implementation */
	virtual void UseAbility() override;

	/** trace check to see if the object can be manipulated */
	FHitData CheckTrace();

	/** winzig's suck power */
	UPROPERTY(EditDefaultsOnly, Category = "Properties")
	float WinzigSuckPower;

//////////////////////////////////////////////////////////////////////////
// Events

	/** tick event */
	virtual void Tick(float DeltaTime) override;

	/* overrides */
	virtual void OnAbilityStart() override;
	virtual void OnAbilityStop() override;

private:
	bool bIsSucking;
};
