

#include "Azuruk.h"
#include "AzurukBaseCharacter.h"

const uint8 DEFAULTFEATURE = uint8(0);

AAzurukBaseCharacter::AAzurukBaseCharacter(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// Don't let Azuruk Characters die
	InitialLifeSpan = 0;

	// Azuruk Property Defaults
	useDistance = 100.f;
	maxFeatures = 1;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	CharacterMovement->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	CharacterMovement->RotationRate = FRotator(0.0f, 560.0f, 0.0f); // ...at this rotation rate
	CharacterMovement->JumpZVelocity = 600.f;
	CharacterMovement->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = PCIP.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUseControllerViewRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = PCIP.CreateDefaultSubobject<UCameraComponent>(this, TEXT("FollowCamera"));
	FollowCamera->AttachTo(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUseControllerViewRotation = false; // Camera does not rotate relative to arm

	TSubobjectPtr<class USkeletalMeshComponent> DefaultMesh;
	DefaultMesh = PCIP.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("DefaultMesh"));
	characterFeatures.Add(DefaultMesh);
}

void AAzurukBaseCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	characterFeatures[0]->SetSkeletalMesh(Mesh->SkeletalMesh);
	characterFeatures[0]->SetAnimClass(Mesh->GetAnimInstance()->GetClass());
}

void AAzurukBaseCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	check(InputComponent);
	// Set up action bindings
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Use", IE_Pressed, this, &AAzurukBaseCharacter::UseObject);
	InputComponent->BindAction("MorphOne", IE_Pressed, this, &AAzurukBaseCharacter::MorphOne);
	InputComponent->BindAction("MorphTwo", IE_Pressed, this, &AAzurukBaseCharacter::MorphTwo);
	// Set up movement bindings
	InputComponent->BindAxis("MoveForward", this, &AAzurukBaseCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AAzurukBaseCharacter::MoveRight);
	// Set up rotation bindings
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

void AAzurukBaseCharacter::MoveForward(float Amount)
{
	if ((Controller!=NULL)&&(Amount!=0.0f))
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

void AAzurukBaseCharacter::MoveRight(float Value)
{
	if ((Controller!=NULL)&&(Value!=0.0f))
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

void AAzurukBaseCharacter::UseObject()
{
	AActor* tActor = GetClosestUse();

	if (Cast<AAzurukBaseCharacter>(tActor) != nullptr)
	{
		this->AddFeatures(Cast<AAzurukBaseCharacter>(tActor)->Mesh);
	}
}

AActor* AAzurukBaseCharacter::GetClosestUse()
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

void AAzurukBaseCharacter::AddFeatures(USkeletalMeshComponent* NewMesh)
{
	if (!characterFeatures.Contains(NewMesh))
	{
		characterFeatures.Add(NewMesh);
	}
}

void AAzurukBaseCharacter::MorphOne() { SetFeatures(uint8(1)); }
void AAzurukBaseCharacter::MorphTwo() { SetFeatures(uint8(2)); }
void AAzurukBaseCharacter::SetFeatures(uint8 index)
{
	if (characterFeatures.IsValidIndex(index) && Mesh->SkeletalMesh != characterFeatures[index]->SkeletalMesh)
	{
		Mesh->SetAnimClass(characterFeatures[index]->GetAnimInstance()->GetClass());
		Mesh->SetSkeletalMesh(characterFeatures[index]->SkeletalMesh);
	}
	else
	{
		Mesh->SetAnimClass(characterFeatures[0]->GetAnimInstance()->GetClass());
		Mesh->SetSkeletalMesh(characterFeatures[0]->SkeletalMesh);
	}
}


