

#pragma once

#include "AzurukBaseCharacter.h"
#include "Components/AzurukMorphingComponent.h"
#include "AzurukPlayerCharacter.generated.h"

namespace EFeatureName
{
	enum Type
	{
		FeatureDefault,
		FeatureOne,
		FeatureTwo,
	};
}

UENUM()
enum ECharacterState
{
	IDLE,
	DNACOLLECT,
	MORPHING,
	STUNNED,
};


/*
 * 
 */
UCLASS()
class AAzurukPlayerCharacter : public AAzurukBaseCharacter
{
	GENERATED_UCLASS_BODY()

	/* Morphing Component for switching features */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Morphing)
	TSubobjectPtr<class UAzurukMorphingComponent> MorphComp;

	/* Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TSubobjectPtr<class USpringArmComponent> CameraBoom;

	/* Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TSubobjectPtr<class UCameraComponent> FollowCamera;

	/* PostInitializeComponents */
	virtual void PostInitializeComponents() override;

	/* Tick */
	virtual void Tick(float DeltaTime) override;

	/* APawn interface */
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

//////////////////////////////////////////////////////////////////////////
// Azuruk Properties

	/* */
	bool InIdleStates();

protected:

	/*  */
	UPROPERTY()
	TEnumAsByte<enum ECharacterState> characterState;

	UPROPERTY(EditDefaultsOnly, Category = Animation)
	UAnimMontage* DNAAnim;

//////////////////////////////////////////////////////////////////////////
// Vitals

private:

	UPROPERTY(EditDefaultsOnly, Category = "Azuruk|Death")
	float deathTimeDilation;

	/* Identifies if pawn is in its stunned state */
	UPROPERTY()
	uint32 bIsStunned : 1;

public:

	/* @RETURN true if Pawn is currently stunned */
	UFUNCTION(BlueprintCallable, Category="Azuruk|Stun", meta=(ToolTip="Checks if Pawn is Stunned"))
	virtual bool IsStunned() const;

	/*
	* Kills pawn.
	* 
	* override - Stops player from dying (teleport map)
	*/
	virtual void Die(float KillingDamage, struct FDamageEvent const& DamageEvent, class AController* Killer, class AActor* DamageCauser);

//////////////////////////////////////////////////////////////////////////
// Movement

private:

	/* Called for forwards/backward input */
	void MoveForward(float Amount);

	/* Called for side to side input */
	void MoveRight(float Amount);

//////////////////////////////////////////////////////////////////////////
// Camera

public:

	UFUNCTION(BlueprintCallable, Category = "Azuruk|Camera")
	virtual void SetCameraOffsetDistance(float NewOffset);

	UFUNCTION(BlueprintCallable, Category = "Azuruk|Camera")
	virtual float GetCameraOffsetDistance();

	UFUNCTION(BlueprintCallable, Category = "Azuruk|Camera")
	virtual FVector GetCameraLocation();

	/*UFUNCTION(BlueprintCallable, Category = "Azuruk|Camera")
	virtual FRotator GetCameraRotation();*/

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Azuruk|Camera")
	float CameraOffsetDistance;

//////////////////////////////////////////////////////////////////////////
// Use Objects

public:

	/* Use object distance */
	UPROPERTY(EditDefaultsOnly, Category = "Azuruk|Using")
	float useDistance;

private:

	UPROPERTY()
	AActor* usedActor;

	/* Called for collecting creature DNA */
	void UseObject();

	/* Get closest usable object
	*
	* TO-DO: Get closest object (If necessary)
	*/
	AActor* GetClosestUse();

	

//////////////////////////////////////////////////////////////////////////
// Morphing

public:

	/* Dynamic Mesh Features Array */
	//UPROPERTY()
	//TArray<UAzurukCharacterFeatures*> featureArray;

	/* */
	void SetDefaultFeatures();

private:

	/*  */
	UPROPERTY()
	uint8 inputFeature;

	/* Max Features */
	UPROPERTY()
	uint8 maxFeatures;

	/* Starts DNA Collection */
	void StartDNACollect();

	/**/
	void StopDNACollect();

	/*  */
	bool CanCollectDNA();

	/* MorphOne and MorphTwo call SetFeatures with Index */
	void MorphOne();
	void MorphTwo();

	/*  */
	void StartMorph(uint8 index);

	/*  */
	void StopMorph();

	/*  */
	void CheckActionInterupt();
};
