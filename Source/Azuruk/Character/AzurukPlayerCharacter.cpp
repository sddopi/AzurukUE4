

#include "Azuruk.h"
#include "AzurukPlayerCharacter.h"

AAzurukPlayerCharacter::AAzurukPlayerCharacter(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// Azuruk Property Defaults
	inputFeature = EFeatureName::FeatureDefault;
	characterState = IDLE;
	usedActor = nullptr;
	useDistance = 100.f;
	maxFeatures = 4;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = PCIP.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUseControllerViewRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = PCIP.CreateDefaultSubobject<UCameraComponent>(this, TEXT("FollowCamera"));
	FollowCamera->AttachTo(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUseControllerViewRotation = false; // Camera does not rotate relative to arm
}

void AAzurukPlayerCharacter::Tick(float DeltaTime)
{
}

//////////////////////////////////////////////////////////////////////////
// Input

void AAzurukPlayerCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	// Set up action bindings
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Use", IE_Pressed, this, &AAzurukPlayerCharacter::UseObject);
	InputComponent->BindAction("MorphOne", IE_Pressed, this, &AAzurukPlayerCharacter::MorphOne);
	InputComponent->BindAction("MorphTwo", IE_Pressed, this, &AAzurukPlayerCharacter::MorphTwo);
	// Set up movement bindings
	InputComponent->BindAxis("MoveForward", this, &AAzurukPlayerCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AAzurukPlayerCharacter::MoveRight);
	// Set up rotation bindings
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

//////////////////////////////////////////////////////////////////////////
// Movement

void AAzurukPlayerCharacter::MoveForward(float Amount)
{
	if ((Controller != NULL) && (Amount != 0.0f))
	{
		CheckActionInterupt();

		const FRotator YawRotation(0, Controller->GetControlRotation().Yaw, 0);
		AddMovementInput(YawRotation.Vector(), Amount);
	}
}

void AAzurukPlayerCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		CheckActionInterupt();

		// Find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		// Get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// Add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

//////////////////////////////////////////////////////////////////////////
// Use Objects

AActor* AAzurukPlayerCharacter::GetClosestUse()
{
	// Get an Array of usable objects
	TArray<struct FOverlapResult> Overlaps;
	GetWorld()->OverlapMulti(Overlaps, this->GetActorLocation(), FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel1, FCollisionShape::MakeSphere(useDistance), FCollisionQueryParams());

	if (Overlaps.Num() != 0)
	{
		return Overlaps[0].GetActor();
	}
	return NULL;
}

void AAzurukPlayerCharacter::UseObject()
{
	usedActor = GetClosestUse();

	AAzurukBaseCharacter* tAChar = Cast<AAzurukBaseCharacter>(usedActor);

	if (tAChar && tAChar->bIsDying && !featureArray.Contains(tAChar->defaultCharacterFeature))
	{
		StartDNACollect();
	}
}

//////////////////////////////////////////////////////////////////////////
// Morphing

void AAzurukPlayerCharacter::StartDNACollect()
{
	if (CanCollectDNA())
	{
		characterState = COLLECTING;

		float AnimDuration = PlayAnimMontage(DNAAnim);

		GetWorldTimerManager().SetTimer(this, &AAzurukPlayerCharacter::StopDNACollect, AnimDuration, false);
	}
}

void AAzurukPlayerCharacter::StopDNACollect()
{
	characterState = IDLE;
	AddFeatures(Cast<AAzurukBaseCharacter>(usedActor)->defaultCharacterFeature);
	usedActor->Destroy();
}

void AAzurukPlayerCharacter::AddFeatures(UAzurukCharacterFeatures* NewFeat)
{
	if (NewFeat->NotNull())
	{
		featureArray.Add(NewFeat);
	}
}

void AAzurukPlayerCharacter::MorphOne()	{ StartMorph( EFeatureName::FeatureOne ); }
void AAzurukPlayerCharacter::MorphTwo() { StartMorph( EFeatureName::FeatureTwo ); }

void AAzurukPlayerCharacter::StartMorph(uint8 index)
{
	if (characterState == IDLE)
	{
		inputFeature = index;
	}

	if (CanMorph())
	{
		characterState = MORPHING;

		float AnimDuration = PlayAnimMontage(MorphAnim);

		GetWorldTimerManager().SetTimer(this, &AAzurukPlayerCharacter::StopMorph, AnimDuration, false);
	}
}

void AAzurukPlayerCharacter::StopMorph()
{
	characterState = IDLE;
	SetFeatures(inputFeature);
}

bool AAzurukPlayerCharacter::CanMorph()
{
	if (featureArray.IsValidIndex(inputFeature))
	{
		bool bIsCorrectStates = (CharacterMovement->MovementMode == EMovementMode::MOVE_Falling ||
								 CharacterMovement->MovementMode == EMovementMode::MOVE_Walking) &&
								 characterState == IDLE;
		bool bFeatureDepleted = featureArray[inputFeature]->isFeatureDepleted();

		return bIsCorrectStates && !bFeatureDepleted;
	}
	return false;
}

bool AAzurukPlayerCharacter::CanCollectDNA()
{
	bool bIsCorrectStates = (CharacterMovement->MovementMode == EMovementMode::MOVE_Falling ||
							 CharacterMovement->MovementMode == EMovementMode::MOVE_Walking) &&
							 characterState == IDLE;
	bool bFeaturesFull = featureArray.Num() == maxFeatures;
	return bIsCorrectStates && !bFeaturesFull;
}

void AAzurukPlayerCharacter::SetFeatures(uint8 index)
{
	if (featureArray[index]->EqualFeatures(Mesh))
	{
		defaultCharacterFeature->SetFeatures(Mesh);
	}
	else
	{
		featureArray[index]->SetFeatures(Mesh);
	}
}

void AAzurukPlayerCharacter::CheckActionInterupt()
{
	if (characterState != IDLE)
	{
		GetWorldTimerManager().ClearAllTimersForObject(this);
		characterState = IDLE;
		StopAllAnimMontages();
	}
}