

#pragma once

#include "AzurukBaseCharacter.h"
#include "AzurukPlayerCharacter.generated.h"

namespace EFeatureName
{
	enum Type
	{
		FeatureOne,
		FeatureTwo,
	};
}

/*
 * 
 */
UCLASS()
class AAzurukPlayerCharacter : public AAzurukBaseCharacter
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

	/* Tick */
	virtual void Tick(float DeltaTime) OVERRIDE;

	/* APawn interface */
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) OVERRIDE;

	/* Dynamic Mesh Features Array */
	UPROPERTY()
	TArray<UAzurukCharacterFeatures*> featureArray;

private:

	/* Active Feature */
	UPROPERTY()
	uint8 usableFeatures;

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
	void AddFeatures(UAzurukCharacterFeatures* NewFeat);

	/* Sets current features to new mesh */
	void SetFeatures(uint8 index);
	/* MorphOne and MorphTwo call SetFeatures with Index */
	void MorphOne();
	void MorphTwo();
};
