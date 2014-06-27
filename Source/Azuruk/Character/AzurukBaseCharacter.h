

#pragma once

#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "AzurukBaseCharacter.generated.h"

/*
 * 
 */
UCLASS(Abstract)
class AAzurukBaseCharacter : public ACharacter
{
	GENERATED_UCLASS_BODY()

public:

	/* PostInitializeComponents */
	virtual void PostInitializeComponents() OVERRIDE;

//////////////////////////////////////////////////////////////////////////
// Damage and Death
	
	/* Take damage, handle death */
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) OVERRIDE;

	/** Returns True if the pawn can die in the current state */
	virtual bool CanDie(float KillingDamage, FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser) const;

	/*
	* Kills pawn.  Server/authority only.
	* @param KillingDamage - Damage amount of the killing blow
	* @param DamageEvent - Damage event of the killing blow
	* @param Killer - Who killed this pawn
	* @param DamageCauser - the Actor that directly caused the damage (i.e. the Projectile that exploded, the Weapon that fired, etc)
	* @returns true if allowed
	*/
	virtual void Die(float KillingDamage, struct FDamageEvent const& DamageEvent, class AController* Killer, class AActor* DamageCauser);

	/** Identifies if pawn is in its dying state */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Health)
	uint32 bIsDying : 1;

private:

	/* switch to ragdoll */
	void SetRagdollPhysics();

//////////////////////////////////////////////////////////////////////////
// Health
public:

	/* Health Value */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Health)
	float maxHealth;

	/* Returns Health Value */
	float GetHealth();

private:

	/* Modify Pawns Health 
	 * Use Negative Input to Heal
	 */
	void ModifyHealth(float Amount);

	/* Health Value */
	float Health;
};
