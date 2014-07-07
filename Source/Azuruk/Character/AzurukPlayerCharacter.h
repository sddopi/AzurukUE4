

#pragma once

#include "AzurukBaseCharacter.h"
#include "AzurukPlayerCharacter.generated.h"

/*
 *
 */
USTRUCT()
struct FCharacterFeatures
{
	GENERATED_USTRUCT_BODY()

private:

	UPROPERTY()
	USkeletalMesh* featureMesh;

	UPROPERTY()
	UClass* featureAnimInstance;

	UPROPERTY()
	float morphTime;

public:

	/* Initialises the Feature Set */
	void InitFeatures(USkeletalMesh* Mesh, UClass* AnimInstance)
	{
		featureMesh = Mesh;
		featureAnimInstance = AnimInstance;
	}
	/* Sets the SkelMesh & AnimInstance on Passed Mesh */
	void SetFeatures(USkeletalMeshComponent* PassedMesh)
	{
		if (this->NotNull() && morphTime > 0.0f)
		{
			PassedMesh->SetAnimClass(featureAnimInstance);
			PassedMesh->SetSkeletalMesh(featureMesh);

		}
	}
	/* Checks if passed features are the same as current */
	bool EqualFeatures(USkeletalMeshComponent* Mesh)
	{
		return Mesh->SkeletalMesh == featureMesh || Mesh->GetAnimInstance()->GetClass() == featureAnimInstance;
	}
	/* Checks if feature is null */
	bool NotNull()
	{
		return featureMesh != nullptr || featureAnimInstance != nullptr;
	}

	void DecreaseMorphTime()
	{
		morphTime = FMath::Min(morphTime - 1.0f, 0.0f);
	}

	void Destroy()
	{
		featureMesh = nullptr;
		featureAnimInstance = nullptr;
		morphTime = NULL;
	}

	FCharacterFeatures()
	{
		featureMesh = nullptr;
		featureAnimInstance = nullptr;
		morphTime = 100.0f;
	}
};

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Azuruk Properties")
	float morphDrainRate;

	/* Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TSubobjectPtr<class USpringArmComponent> CameraBoom;

	/* Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TSubobjectPtr<class UCameraComponent> FollowCamera;

	/* PostInitializeComponents */
	virtual void PostInitializeComponents() OVERRIDE;

	/* APawn interface */
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) OVERRIDE;

	/* */
	FCharacterFeatures* GetCharacterFeature(uint8 index);

private:

	/* Dynamic Mesh Features Array */
	UPROPERTY()
	TArray<FCharacterFeatures> featureArray;

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
	void AddFeatures(USkeletalMeshComponent* NewMesh);

	/* Sets current features to new mesh */
	void SetFeatures(uint8 index);
	/* MorphOne and MorphTwo call SetFeatures with Index */
	void MorphOne();
	void MorphTwo();
};
