

#pragma once

#include "GameFramework/Character.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/SpringArmComponent.h"
#include "AzurukBaseCharacter.generated.h"

/*
 * 
 */
UCLASS()
class AAzurukBaseCharacter : public ACharacter
{
	GENERATED_UCLASS_BODY()

	/* Use object distance */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Azuruk Properties")
		float useDistance;
	
	/* Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		TSubobjectPtr<class USpringArmComponent> CameraBoom;

	/* Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		TSubobjectPtr<class UCameraComponent> FollowCamera;

protected:

	/* Dynamic Mesh Features Array */
	UPROPERTY()
		TArray<USkeletalMeshComponent*> characterFeatures;
	
	/* Called for forwards/backward input */
	void MoveForward(float Value);

	/* Called for side to side input */
	void MoveRight(float Value);

	/* Called for collecting creature DNA */
	void UseObject();

	/* Get closest usable object 
	 *
	 * TO-DO: Get closest object (If necessary)	 
	 */
	AActor* GetClosestUse();

	/* Adds features to features array */
	void AddFeatures(USkeletalMeshComponent* NewMesh);

	/* Sets current features to new mesh 
	 * 
	 * MorphOne and MorphTwo call SetFeatures with Index
	 */
	void SetFeatures(uint8 index);
	void MorphOne();
	void MorphTwo();

	/* PostInitializeComponents */
	virtual void PostInitializeComponents() OVERRIDE;

	/* APawn interface */
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) OVERRIDE;	
};
