

#pragma once
#include "Object.h"
#include "Tickable.h"
#include "AzurukAbilityBase.generated.h"

UENUM()
enum ECastType
{
	Casted,
	Casted_Charged,
	Channeled,
	Instant
};

USTRUCT()
struct FAbilityAnim
{
	GENERATED_USTRUCT_BODY()

	/** animation played on pawn (1st person view) */
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* Pawn1P;

	/** animation played on pawn (3rd person view) */
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* Pawn3P;
};

USTRUCT()
struct FAbilityData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Ability|Properties")
	float MaxCastTime;

	UPROPERTY(EditAnywhere, Category = "Ability|Properties")
	float ChannelInterval;

	UPROPERTY(EditAnywhere, Category = "Ability|Properties")
	float MaxOverCastTime;

	UPROPERTY(EditAnywhere, Category = "Ability|Properties")
	float AbilityCooldownTime;

	UPROPERTY(EditAnywhere, Category = "Ability|Properties")
	TEnumAsByte<ECastType> AbilityCastType;

	FAbilityData()
	{
		MaxCastTime = 3.0f;
		ChannelInterval = 1.0f;
		MaxOverCastTime = 1.0f;
		AbilityCooldownTime = 5.0f;
		AbilityCastType = Instant;
	}
};

/**
 * Base ability
 */
UCLASS(Abstract, Blueprintable)
class AAzurukAbilityBase : public AActor
{
	GENERATED_UCLASS_BODY()

	/** perform initial setup */
	virtual void PostInitializeComponents() override;

//////////////////////////////////////////////////////////////////////////
// Input

	UFUNCTION(BlueprintCallable, Category = "Ability|Input")
	virtual void InputPressed();

	UFUNCTION(BlueprintCallable, Category = "Ability|Input")
	virtual void InputReleased();

	UPROPERTY(EditAnywhere, Category = "Ability|Input")
	FString KeyBinding;
	
	UFUNCTION(BlueprintCallable, Category = "Ability|Input")
	void SetKeyBinding(FString NewKeyBinding);

	UFUNCTION(BlueprintCallable, Category = "Ability|Input")
	FString GetKeyBinding();

//////////////////////////////////////////////////////////////////////////
// Events

	/** tick event */
	virtual void Tick(float DeltaTime) override;

	/** ability was added to pawn */
	virtual void OnAddAbility(class AAzurukBaseCharacter* NewOwner);

	/** ability removed from pawn */
	virtual void OnRemoveAbility();

	void OnAbilityStart();
	void OnAbilityStop();
	void OnAbilityInitialized();

//////////////////////////////////////////////////////////////////////////
// Replication

	UFUNCTION()
		void OnRep_AbilityOwner();

//////////////////////////////////////////////////////////////////////////
// Reading Data

public:

	/** set the owner of the ability */
	void  SetAbilityOwner(class AAzurukBaseCharacter* Owner);

	/** get owner mesh */
	UFUNCTION()
	USkeletalMeshComponent* GetOwnerMesh() const;

protected:

	/** pawn owner */
	UPROPERTY() //Transient, ReplicatedUsing=OnRep_AbilityOwner
	class AAzurukBaseCharacter* AbilityOwner;
	
	/** ability attach socket */
	UPROPERTY(EditDefaultsOnly, Category = "Ability|Mesh")
	FName AttachPoint;

	/** ability data */
	UPROPERTY(EditDefaultsOnly, Category = "Config")
	FAbilityData AbilityConfig;

	/** cast loop audio cue */
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	UAudioComponent* CastLoopSound;

	/** cast audio cue */
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	UAudioComponent* CastSound;

	/** FX for cast loop */
	UPROPERTY(EditDefaultsOnly, Category = "Ability|Effects")
	UParticleSystem* CastLoopFX;

	/** spawned component for cast loop FX */
	UPROPERTY()
	UParticleSystemComponent* CastLoopPSC;

	/** FX for cast */
	UPROPERTY(EditDefaultsOnly, Category = "Ability|Effects")
	UParticleSystem* CastFX;

	/** spawned component for cast */
	UPROPERTY()
	UParticleSystemComponent* CastPSC;

	/** cast loop animation */
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	FAbilityAnim CastLoopAnim;

	/** cast animation */
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	FAbilityAnim CastAnim;

//////////////////////////////////////////////////////////////////////////
// Ability Usage

	/** ability specific usage implementation */
	virtual void UseAbility() PURE_VIRTUAL(AAzurukAbilityBase::UseAbility,);

	/** play ability sounds */
	UAudioComponent* PlayAbilitySound(USoundCue* Sound);

	/** play ability animations */
	float PlayAbilityAnimation(const FAbilityAnim& Animation);

	/** stop playing ability animations */
	void StopAbilityAnimation(const FAbilityAnim& Animation);

	/** get the attach location of the ability */
	FVector GetAttachLocation() const;

	/** get the attach rotation of the ability */
	FVector GetAttachDirection() const;

private:
	bool bIsChanneled;
	bool bIsCasted;
	bool bIsOnCooldown;
	bool bIsCharged;
	bool bIsInstant;
	bool bIsAbilityInitialized;
	float CurrentIntervalTime;
	float CurrentCooldownTime;
	float CurrentCastTime;
	float CurrentChargeTime;
};
