

#pragma once

#include "AzurukBaseCharacter.h"
#include "AzurukPlayerCharacter.generated.h"

namespace EFeatureName
{
	enum Type
	{
		FeatureOne,
		FeatureTwo,
		FeatureDefault,
	};
}

UENUM()
enum ECharacterState
{
	IDLE,
	COLLECTING,
	MORPHING,
};


/*
 * 
 */
UCLASS()
class AAzurukPlayerCharacter : public AAzurukBaseCharacter
{
	GENERATED_UCLASS_BODY()

	/* Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TSubobjectPtr<class USpringArmComponent> CameraBoom;

	/* Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TSubobjectPtr<class UCameraComponent> FollowCamera;

	/* Tick */
	virtual void Tick(float DeltaTime) OVERRIDE;

	/* APawn interface */
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) OVERRIDE;

//////////////////////////////////////////////////////////////////////////
// Azuruk Properties

protected:

	UPROPERTY(EditDefaultsOnly, Category = Animation)
	UAnimMontage* DNAAnim;

	/*  */
	UPROPERTY()
	TEnumAsByte<enum ECharacterState> characterState;

//////////////////////////////////////////////////////////////////////////
// Movement

private:

	/* Called for forwards/backward input */
	void MoveForward(float Amount);

	/* Called for side to side input */
	void MoveRight(float Amount);

//////////////////////////////////////////////////////////////////////////
// Use Objects

public:

	/* Use object distance */
	UPROPERTY(EditDefaultsOnly, Category = "Azuruk Properties")
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
	UPROPERTY()
	TArray<UAzurukCharacterFeatures*> featureArray;

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

	/* Adds features to features array */
	void AddFeatures(UAzurukCharacterFeatures* NewFeat);

	/* MorphOne and MorphTwo call SetFeatures with Index */
	void MorphOne();
	void MorphTwo();

	/*  */
	void StartMorph(uint8 index);

	/*  */
	void StopMorph();

	/*  */
	bool CanMorph();

	/* Sets current features to new mesh */
	void SetFeatures(uint8 index);

	/*  */
	void CheckActionInterupt();
};
