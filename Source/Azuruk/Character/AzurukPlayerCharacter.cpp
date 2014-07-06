

#include "Azuruk.h"
#include "AzurukPlayerCharacter.h"


AAzurukPlayerCharacter::AAzurukPlayerCharacter(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// Azuruk Property Defaults
	useDistance = 100.f;
	morphTime = 100.f;
	activeFeature = 0;

	morphTimes.Add(morphTime);

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

void AAzurukPlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	// Assign Default Features
	if (Mesh->SkeletalMesh != nullptr && Mesh->GetAnimInstance() != nullptr)
	{
		defaultMesh = Mesh->SkeletalMesh;
		defaultAnimInstance = Mesh->GetAnimInstance()->GetClass();
	}
}

void AAzurukPlayerCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	check(InputComponent);
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

void AAzurukPlayerCharacter::MoveForward(float Amount)
{
	if ((Controller != NULL) && (Amount != 0.0f))
	{
		// Find forward vector
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Get forward vector
		const FVector Direction = FRotationMatrix(Rotation).GetUnitAxis(EAxis::X);
		// Add movement in that direction
		AddMovementInput(Direction, Amount);
	}
}

void AAzurukPlayerCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// Find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// Add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AAzurukPlayerCharacter::UseObject()
{
	AActor* tActor = GetClosestUse();

	if (Cast<AAzurukBaseCharacter>(tActor) != nullptr && Cast<AAzurukBaseCharacter>(tActor)->bIsDying)
	{
		this->AddFeatures(Cast<AAzurukBaseCharacter>(tActor)->Mesh);
	}
}

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

void AAzurukPlayerCharacter::AddFeatures(USkeletalMeshComponent* NewMesh)
{
	if (!characterFeatures.Contains(NewMesh))
	{
		characterFeatures.Add(NewMesh);
	}
}

void AAzurukPlayerCharacter::MorphOne()
{
	if (characterFeatures.IsValidIndex(0))
	{
		SetFeatures(uint8(0));
	}
}
void AAzurukPlayerCharacter::MorphTwo()
{
	if (characterFeatures.IsValidIndex(1))
	{
		SetFeatures(uint8(1));
	}
}
void AAzurukPlayerCharacter::SetFeatures(uint8 index)
{

	if (Mesh->SkeletalMesh != characterFeatures[index]->SkeletalMesh)
	{
		Mesh->SetAnimClass(characterFeatures[index]->GetAnimInstance()->GetClass());
		Mesh->SetSkeletalMesh(characterFeatures[index]->SkeletalMesh);
	}
	else
	{
		Mesh->SetAnimClass(defaultAnimInstance);
		Mesh->SetSkeletalMesh(defaultMesh);
	}
}

float AAzurukPlayerCharacter::GetMorphTime(uint8 index)
{
	return morphTimes[index];
}