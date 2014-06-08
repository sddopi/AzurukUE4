

#include "Azuruk.h"
#include "AzurukBaseCharacter.h"


AAzurukBaseCharacter::AAzurukBaseCharacter(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// Don't let Azuruk Characters die
	InitialLifeSpan = 0;

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
}

void AAzurukBaseCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	check(InputComponent);
	// Set up action bindings
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Use", IE_Pressed, this, &AAzurukBaseCharacter::UseObject);
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
	AActor* useObj = GetClosestUse();

	if (Cast<AAzurukBaseCharacter>(useObj)!=nullptr)
	{
		AAzurukBaseCharacter* usePawn = Cast<AAzurukBaseCharacter>(useObj);
	}
}

AActor* AAzurukBaseCharacter::GetClosestUse()
{
	// Get an Array of usable objects
	TArray<struct FOverlapResult> Overlaps;
	GetWorld()->OverlapMulti(Overlaps, this->GetActorLocation(), FQuat::Identity, ECollisionChannel::ECC_Pawn, FCollisionShape::MakeSphere(UseDistance), FCollisionQueryParams());

	if (Overlaps.Num()>0)
	{
		return Overlaps[0].GetActor();
	}
	return NULL;
}


