

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

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class AAzurukAbilityBase : public AActor
{
	GENERATED_UCLASS_BODY()

	virtual void Tick(float DeltaTime);
	virtual bool IsTickable() const;

	virtual class UWorld* GetWorld() const OVERRIDE;

	//////////////////////////////////////////////////////////////////////////
	// Input

	virtual void InputPressed();
	virtual void InputReleased();

	UPROPERTY(EditAnywhere, Category = "Ability Properties")
		FString KeyBinding;

	void SetKeyBinding(FString NewKeyBinding);

	FString GetKeyBinding();

	//////////////////////////////////////////////////////////////////////////
	// Ability Manager

	/* ability was added to pawn */
	virtual void OnAddAbility(AAzurukBaseCharacter* NewOwner);

	/* ability removed from pawn */
	virtual void OnRemoveAbility();

	UFUNCTION(BlueprintImplementableEvent, Category = "Ability|Events")
		void OnAbilityStart();

	UFUNCTION(BlueprintImplementableEvent, Category = "Ability|Events")
		void OnAbilityStop();

	UFUNCTION(BlueprintImplementableEvent, Category = "Ability|Events")
		void OnAbilityInitialized();

	virtual void Initialize(APawn* owner, APawn* instigator);

public:
	UPROPERTY(EditAnywhere, Category = "Ability Properties")
		TEnumAsByte<ECastType> AbilityCastType;

	void  SetAbilityOwner(APawn* Owner);

protected:
	UPROPERTY(EditAnywhere, Category = "Ability Properties")
		float MaxCastTime;

	UPROPERTY(EditAnywhere, Category = "Ability Properties")
		float ChannelInterval;

	UPROPERTY(EditAnywhere, Category = "Ability Properties")
		float MaxOverCastTime;

	UPROPERTY(EditAnywhere, Category = "Ability Properties")
		float AbilityCooldownTime;

	UPROPERTY(BlueprintReadOnly, Category = "Ability")
		APawn* AbilityOwner;

	bool IsAbilityInitialized;

private:
	bool isChanneled;
	bool isCasted;
	bool isOnCooldown;
	bool isCharged;
	float currentIntervalTime;
	float currentCooldownTime;
	float currentCastTime;
	float currentChargeTime;
};
