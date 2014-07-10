

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
// Azuruk Properties

	UPROPERTY()
	UAzurukCharacterFeatures* defaultCharacterFeature;

	UPROPERTY(EditDefaultsOnly, Category = "Azuruk Properties")
	float maxMorphTime;

protected:

	UPROPERTY(EditDefaultsOnly, Category = Animation)
	UAnimMontage* MorphAnim;	

//////////////////////////////////////////////////////////////////////////
// Animations

public:
	
	/* play anim montage */
	virtual float PlayAnimMontage(class UAnimMontage* AnimMontage, float InPlayRate = 1.f, FName StartSectionName = NAME_None) OVERRIDE;

	/* stop playing montage */
	virtual void StopAnimMontage(class UAnimMontage* AnimMontage) OVERRIDE;

	/* stop playing all montages */
	void StopAllAnimMontages();

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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	uint32 bIsDying : 1;

private:

	/* switch to ragdoll */
	void SetRagdollPhysics();

//////////////////////////////////////////////////////////////////////////
// Health
public:

	/* Return Health Value */
	float GetHealth();
	
	/* Returns Max Health Value */
	float GetMaxHealth() const;

	/* check if pawn is still alive */
	bool IsAlive() const;

private:

	/* Health Value */
	float Health;

	/* Modify Pawns GetHealth() 
	 * Use Negative Input to Heal
	 */
	void ModifyHealth(float Amount);

//////////////////////////////////////////////////////////////////////////
// Abilities

public:

	/* Ability manager */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Componenets)
	TSubclassOf<class UAzurukAbilityManager> AbilityManager;

	/* Button one */
	UFUNCTION()
	void ActionButtonOne();
	UFUNCTION()
	void ActionButtonOneReleased();
};
