

#pragma once

#include "AzurukBaseCharacter.h"
#include "AzurukPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AAzurukPlayerCharacter : public AAzurukBaseCharacter
{
	GENERATED_UCLASS_BODY()

	/* PostInitializeComponents */
	virtual void PostInitializeComponents() OVERRIDE;

	/* APawn interface */
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) OVERRIDE;	

	/* Use object distance */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Azuruk Properties")
	float useDistance;

	/* Use object distance */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Azuruk Properties")
	float morphTime;

	float GetMorphTime(uint8 index);

	/* Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TSubobjectPtr<class USpringArmComponent> CameraBoom;

	/* Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TSubobjectPtr<class UCameraComponent> FollowCamera;

private:

	/* Dynamic Mesh Features Array */
	UPROPERTY()
	TArray<USkeletalMeshComponent*> characterFeatures;

	/* Morph Bar Times */
	UPROPERTY()
	TArray<float> morphTimes;

	/* Active Feature */
	UPROPERTY()
	uint8 activeFeature;

	UPROPERTY(EditDefaultsOnly, Category = "Azuruk Properties")
	USkeletalMesh* defaultMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Azuruk Properties")
	UClass* defaultAnimInstance;

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
};
