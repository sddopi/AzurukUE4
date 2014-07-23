

#include "Azuruk.h"
#include "AzurukAbilityProjectile_Winzig.h"


AAzurukAbilityProjectile_Winzig::AAzurukAbilityProjectile_Winzig(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	WinzigSuckPower = 500.f;
	AbilityConfig.AbilityCooldownTime = 0.f;
	bIsSucking = false;
}

void AAzurukAbilityProjectile_Winzig::UseAbility()
{
	
}

FHitData AAzurukAbilityProjectile_Winzig::CheckTrace()
{
	FVector ShootDir = GetAdjustedAim();
	FVector Origin = GetAttachLocation();

	// trace from camera to check what's under crosshair
	const float ProjectileAdjustRange = 10000.0f;
	const FVector StartTrace = GetCameraDamageStartLocation(ShootDir);
	const FVector EndTrace = StartTrace + ShootDir * ProjectileAdjustRange;

	//FHitResult Impact = AbilityTrace(StartTrace, EndTrace);
	static FName AbilityUseTag = FName(TEXT("AbilityTrace"));

	// Perform trace to retrieve hit info
	FCollisionQueryParams TraceParams(AbilityUseTag, true, Instigator);
	TraceParams.bTraceAsyncScene = true;
	TraceParams.bReturnPhysicalMaterial = true;

	FHitResult Impact(ForceInit);
	GetWorld()->LineTraceSingle(Impact, StartTrace, EndTrace, ECC_Visibility, TraceParams);

	FName Winzig = "Winzig";
	FHitData HitData;
	AActor* HitActor = HitData.HitResult.GetActor();
	HitData.HitResult = Impact;
	HitData.HitLocation = Impact.Location;

		if (Impact.GetActor()->ActorHasTag(Winzig))
		{
			HitData.bCanWinzigUse = true;
		}
		else
		{
			HitData.bCanWinzigUse = false;
		}
	

	return HitData;
}

void AAzurukAbilityProjectile_Winzig::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FHitData HitData;

	if (bIsSucking)
	{
		HitData = CheckTrace();

		if (HitData.HitResult.GetActor())
		{
			if (HitData.bCanWinzigUse)
			{
				AStaticMeshActor* SMA = Cast<AStaticMeshActor>(HitData.HitResult.GetActor());
				AAzurukPlayerCharacter* PC = Cast<AAzurukPlayerCharacter>(AbilityOwner);

				FVector PlayerLoc = PC->GetActorLocation();
				FVector HitActorLoc = SMA->GetActorLocation();

				FVector Direction = PlayerLoc - HitActorLoc;
				FVector Reduction = FVector(0.3f, 0.3f, 0.3f);
				Direction.Normalize();

				// reduce all values and multiply by suck power
				Direction = Direction * Reduction;
				FVector Blended = Direction * WinzigSuckPower;
				FVector SMAVelocity = SMA->GetVelocity();

				// interp
				Blended = FMath::VInterpTo(SMA->GetActorLocation(), Direction, DeltaTime, 5.f);
				DrawDebugLine(GetWorld(), HitActorLoc, Blended, FColor(0, 255, 0), false, 1.f);

				SMA->GetRootPrimitiveComponent()->SetPhysicsLinearVelocity(Blended);
			}
		}
	}
}

void AAzurukAbilityProjectile_Winzig::OnAbilityStart()
{
	Super::OnAbilityStart();

	bIsSucking = true;
}

void AAzurukAbilityProjectile_Winzig::OnAbilityStop()
{
	Super::OnAbilityStop();

	bIsSucking = false;
}