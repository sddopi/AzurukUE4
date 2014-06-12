

#pragma once

#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "AzurukBaseCharacter.generated.h"

/**
*
*/
USTRUCT()
struct FCharacterFeatures
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	USkeletalMesh* charMesh;

	UPROPERTY()
	UAnimInstance* charAnim;

	//Constructor
	FCharacterFeatures()
	{

	}

	FCharacterFeatures(USkeletalMesh* mesh, UAnimInstance* anim)
	{
		charMesh = mesh;
		charAnim = anim;
	}
};

/**
 * 
 */
UCLASS()
class AAzurukBaseCharacter : public ACharacter
{
	GENERATED_UCLASS_BODY()

	/* Use object distance */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Azuruk Properties")
		float UseDistance;

	/* Character Name */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Azuruk Properties")
		FName CharacterName;
	
	/* Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		TSubobjectPtr<class USpringArmComponent> CameraBoom;

	/* Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		TSubobjectPtr<class UCameraComponent> FollowCamera;

protected:	

	/* Called for forwards/backward input */
	void MoveForward(float Value);

	/* Called for side to side input */
	void MoveRight(float Value);

	/* Called for collecting creature DNA */
	void UseObject();

	/* Get closest usable object */
	AActor* GetClosestUse();

	/* APawn interface */
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) OVERRIDE;	
};
