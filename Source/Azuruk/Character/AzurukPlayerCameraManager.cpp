

#include "Azuruk.h"
#include "AzurukPlayerCameraManager.h"

AAzurukPlayerCameraManager::AAzurukPlayerCameraManager(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
}

void AAzurukPlayerCameraManager::UpdateCamera(float DeltaTime)
{
	Super::UpdateCamera(DeltaTime);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("update camera"));
}

void AAzurukPlayerCameraManager::UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime)
{
	FVector Loc, Pos, HitLocation, HitNormal, EyeLoc, FinalPos;
	FRotator Rot, EyeRot;
	FMinimalViewInfo OrigPOV;
	FMath math = FMath();

	//It should be header file, but for now it will work.
	FVector LowOffset = FVector(-100.0f, 0, 20.0f);
	FVector MidOffset = FVector(-100.0f, 0, 20.0f);
	FVector HighOffset = FVector(-50.0f, 0, 100.0f);

	FVector FinalOffset = MidOffset;

	OrigPOV = OutVT.POV;
	OutVT.Target->GetActorEyesViewPoint(EyeLoc, EyeRot);
	Loc = OutVT.Target->GetActorLocation();

	//DrawDebugString(FVector(0, 0, 0), EyeRot.ToString());
	FVector const Offset = FVector(-150.0f, 0.0f, 0.0f);
	FinalPos = EyeLoc;
	FinalPos += FRotationMatrix(EyeRot).TransformVector(FinalOffset);

	OutVT.POV.Location = FinalPos;
	OutVT.POV.Rotation = EyeRot;
}
