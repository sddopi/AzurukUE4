

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
class UAzurukAbilityBase : public UObject
{
	GENERATED_UCLASS_BODY()

	virtual void Tick(float DeltaTime);
	virtual bool IsTickable() const;

	virtual class UWorld* GetWorld() const OVERRIDE;

	virtual void InputPressed();
	virtual void InputReleased();

	UFUNCTION(BlueprintImplementableEvent, Category = "Ability|Events")
		void OnAbilityStart();

	UFUNCTION(BlueprintImplementableEvent, Category = "Ability|Events")
		void OnAbilityStop();

	UFUNCTION(BlueprintImplementableEvent, Category = "Ability|Events")
		void OnAbilityInitialized();

	virtual void Initialize(APawn* owner, AController* instigator);

public:
	UPROPERTY(EditAnywhere, Category = "Ability Properties")
		TEnumAsByte<ECastType> AbilityCastType;

	void FORCEINLINE SetAbilityOwner(APawn* Owner) { AbilityOwner = Owner; };
	void FORCEINLINE SetInstigator(AController* instigator) { Instigator = instigator; };

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

	UPROPERTY(BlueprintReadOnly, Category = "Ability")
		AController* Instigator;

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
