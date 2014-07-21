

#include "Azuruk.h"
#include "AzurukPlayerCharacter.h"

AAzurukPlayerCharacter::AAzurukPlayerCharacter(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// Azuruk Property Defaults
	characterState = IDLE;
	usedActor = nullptr;
	useDistance = 100.f;
	maxFeatures = 4;
	bIsStunned = false;

	// Camera defaults
	CameraOffsetDistance = 300.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	//
	MorphComp = PCIP.CreateDefaultSubobject<UAzurukMorphingComponent>(this, TEXT("MorphComp"));

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

void AAzurukPlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	MorphComp->AddMorph(defaultCharacterFeature);
}

void AAzurukPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AAzurukPlayerCharacter::InIdleStates()
{
	return (CharacterMovement->MovementMode == EMovementMode::MOVE_Falling ||
			CharacterMovement->MovementMode == EMovementMode::MOVE_Walking) &&
			characterState == IDLE;
}

//////////////////////////////////////////////////////////////////////////
// Vitals

bool AAzurukPlayerCharacter::IsStunned() const
{
	return bIsStunned;
}

void AAzurukPlayerCharacter::Die(float KillingDamage, struct FDamageEvent const& DamageEvent, class AController* Killer, class AActor* DamageCauser)
{
	if (CanDie(KillingDamage, DamageEvent, Killer, DamageCauser))
	{
		APlayerController* PC = Cast<APlayerController>(GetController());

		if (PC)
		{
			bIsStunned = true;
			GetWorld()->GetWorldSettings()->TimeDilation = deathTimeDilation;
			DisableInput(PC);
		}
	}
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
// Camera

void AAzurukPlayerCharacter::SetCameraOffsetDistance(float NewOffset)
{
	CameraOffsetDistance = NewOffset;
}

float AAzurukPlayerCharacter::GetCameraOffsetDistance()
{
	return CameraOffsetDistance;
}

FVector AAzurukPlayerCharacter::GetCameraLocation()
{
	return FollowCamera->GetComponentLocation();
}

//FRotator AAzurukPlayerCharacter::GetCameraRotation()
//{
//	return FollowCamera->GetControlRotation();
//}

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

	if (tAChar && tAChar->bIsDying && !(MorphComp->ContainsMorph(tAChar->defaultCharacterFeature)))
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
		characterState = DNACOLLECT;

		float AnimDuration = PlayAnimMontage(DNAAnim);

		GetWorldTimerManager().SetTimer(this, &AAzurukPlayerCharacter::StopDNACollect, AnimDuration, false);
	}
}

void AAzurukPlayerCharacter::StopDNACollect()
{
	characterState = IDLE;
	MorphComp->AddMorph(Cast<AAzurukBaseCharacter>(usedActor)->defaultCharacterFeature);
	usedActor->Destroy();
}

void AAzurukPlayerCharacter::MorphOne()	{ StartMorph( EFeatureName::FeatureOne ); }
void AAzurukPlayerCharacter::MorphTwo() { StartMorph( EFeatureName::FeatureTwo ); }

void AAzurukPlayerCharacter::StartMorph(uint8 index)
{
	if (MorphComp->CanMorph(index))
	{
		characterState = MORPHING;

		inputFeature = inputFeature == index ?
					   EFeatureName::FeatureDefault :
					   index;

		float AnimDuration = PlayAnimMontage(morphAnim);

		GetWorldTimerManager().SetTimer(this, &AAzurukPlayerCharacter::StopMorph, AnimDuration, false);
	}
}

void AAzurukPlayerCharacter::StopMorph()
{
	MorphComp->SetMorph(inputFeature);
	characterState = IDLE;
}

bool AAzurukPlayerCharacter::CanCollectDNA()
{
	bool bIsCorrectStates = (CharacterMovement->MovementMode == EMovementMode::MOVE_Falling ||
							 CharacterMovement->MovementMode == EMovementMode::MOVE_Walking) &&
							 characterState == IDLE;
	//bool bFeaturesFull = featureArray.Num() == maxFeatures;
	return bIsCorrectStates;
}

void AAzurukPlayerCharacter::CheckActionInterupt()
{
	if (characterState != IDLE)
	{
		switch (characterState)
		{
			case DNACOLLECT:
				GetWorldTimerManager().ClearTimer(this, &AAzurukPlayerCharacter::StopDNACollect);
				break;
			case MORPHING:
				GetWorldTimerManager().ClearTimer(this, &AAzurukPlayerCharacter::StopMorph);
				break;
		}
		characterState = IDLE;
		StopAllAnimMontages();
	}
}