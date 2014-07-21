

#pragma once

#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "ParticleDefinitions.h"
#include "Kismet/GameplayStatics.h"
#include "Abilities/AzurukAbilityBase.h"
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
	virtual void PostInitializeComponents() override;

	AAzurukBaseCharacter* GetBaseCharacter();

//////////////////////////////////////////////////////////////////////////
// Azuruk Properties

	UAzurukCharacterFeatures* defaultCharacterFeature;

	UPROPERTY(EditDefaultsOnly, Category = "Azuruk|Morphing")
	float maxMorphTime;

	UPROPERTY(EditDefaultsOnly, Category = "Azuruk|Morphing")
	UAnimMontage* morphAnim;

	UPROPERTY(EditDefaultsOnly, Category = "Azuruk|Vitals")
	UParticleSystem* deathParticle;

//////////////////////////////////////////////////////////////////////////
// Animations

public:
	
	/* play anim montage */
	virtual float PlayAnimMontage(class UAnimMontage* AnimMontage, float InPlayRate = 1.f, FName StartSectionName = NAME_None) override;

	/* stop playing montage */
	virtual void StopAnimMontage(class UAnimMontage* AnimMontage) override;

	/* stop playing all montages */
	void StopAllAnimMontages();

//////////////////////////////////////////////////////////////////////////
// Vitals
	
	/* Take damage, handle death */
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;

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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Azuruk|Death")
	uint32 bIsDying : 1;

	/* Destroyed */
	virtual void Destroyed() override;

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

	/* Ability list */
	UPROPERTY()
	TArray<class AAzurukAbilityBase*> Abilities;

	/* ability being used */
	bool bIsCasting;

	/**
	* add ability to pawn
	*
	* @param Ability Ability to add.
	*/
	UFUNCTION(BlueprintCallable, Category = "Ability")
	void AddAbility(class AAzurukAbilityBase* Ability);

	/**
	* remove ability from pawn
	*
	* @param Ability Ability to remove.
	*/
	UFUNCTION(BlueprintCallable, Category = "Ability")
	void RemoveAbility(class AAzurukAbilityBase* Ability);

	/**
	* destroy all abilities in array
	*/
	UFUNCTION(BlueprintCallable, Category = "Ability")
	void DestroyAbilities();

	/**
	* Find in pawn
	*
	* @param AbilityClass	Class of ability to find.
	*/
	class AAzurukAbilityBase* FindAbility(TSubclassOf<class AAzurukAbilityBase> AbilityClass);

	/**
	* find ability that is bound to specific key
	* 
	* @param KeyBinding key ability is bound to
	*/
	class AAzurukAbilityBase* FindAbilityBoundToKey(FString KeyBinding);

	/**
	* start ability with defined keybind
	* 
	* @param KeyBinding key ability is bound to
	*/
	void StartAbility(FString KeyBinding);

	/**
	* stop ability with defined keybind
	*
	* @param KeyBinding key ability is bound to
	*/
	void StopAbility(FString KeyBinding);


//////////////////////////////////////////////////////////////////////////
// Input

public:

	/** setup pawn specific input handlers */
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	/* Button one */
	void AbilityButtonOne();

	void AbilityButtonOneReleased();
};
