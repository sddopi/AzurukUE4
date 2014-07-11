

#include "Azuruk.h"
#include "AzurukAbilityProjectile.h"
#include "AzurukProjectile.h"


AAzurukAbilityProjectile::AAzurukAbilityProjectile(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
}

void AAzurukAbilityProjectile::OnAbilityStart()
{
	Super::OnAbilityStart();
}

void AAzurukAbilityProjectile::OnAbilityStop()
{
	Super::OnAbilityStop();
}

void AAzurukAbilityProjectile::OnAbilityInitialized()
{
	Super::OnAbilityInitialized();
}

void AAzurukAbilityProjectile::ApplyAbilityConfig(FProjectileAbilityData& Data)
{
	Data = ProjectileConfig;
}

//////////////////////////////////////////////////////////////////////////
// Ability Usage

void AAzurukAbilityProjectile::UseAbility()
{
	FVector ShootDir = GetAdjustedAim();
	FVector Origin = GetAttachLocation();

	// trace from camera to check what's under crosshair
	const float ProjectileAdjustRange = 10000.0f;
	const FVector StartTrace = GetCameraDamageStartLocation(ShootDir);
	const FVector EndTrace = StartTrace + ShootDir * ProjectileAdjustRange;
	FHitResult Impact = AbilityTrace(StartTrace, EndTrace);

	// and adjust directions to hit that actor
	if (Impact.bBlockingHit)
	{
		const FVector AdjustedDir = (Impact.ImpactPoint - Origin).SafeNormal();
		bool bWeaponPenetration = false;

		const float DirectionDot = FVector::DotProduct(AdjustedDir, ShootDir);
		if (DirectionDot < 0.0f)
		{
			// shooting backwards = weapon is penetrating
			bWeaponPenetration = true;
		}
		else if (DirectionDot < 0.5f)
		{
			// check for weapon penetration if angle difference is big enough
			// raycast along weapon mesh to check if there's blocking hit

			FVector MuzzleStartTrace = Origin - GetAttachDirection() * 150.0f;
			FVector MuzzleEndTrace = Origin;
			FHitResult MuzzleImpact = AbilityTrace(MuzzleStartTrace, MuzzleEndTrace);

			if (MuzzleImpact.bBlockingHit)
			{
				bWeaponPenetration = true;
			}
		}

		if (bWeaponPenetration)
		{
			// spawn at crosshair position
			Origin = Impact.ImpactPoint - ShootDir * 10.0f;
		}
		else
		{
			// adjust direction to hit
			ShootDir = AdjustedDir;
		}
	}

	ServerFireProjectile(Origin, ShootDir);
}

bool AAzurukAbilityProjectile::ServerFireProjectile_Validate(FVector Origin, FVector_NetQuantizeNormal ShootDir)
{
	return true;
}

void AAzurukAbilityProjectile::ServerFireProjectile_Implementation(FVector Origin, FVector_NetQuantizeNormal ShootDir)
{
	FTransform SpawnTM(ShootDir.Rotation(), Origin);
	AAzurukProjectile* Projectile = Cast<AAzurukProjectile>(UGameplayStatics::BeginSpawningActorFromClass(this, ProjectileConfig.ProjectileClass, SpawnTM));
	if (Projectile)
	{
		Projectile->Instigator = Instigator;
		Projectile->SetOwner(this);
		Projectile->InitVelocity(ShootDir);

		UGameplayStatics::FinishSpawningActor(Projectile, SpawnTM);
	}
}

FVector AAzurukAbilityProjectile::GetCameraAim() const
{
	AAzurukPlayerController* const PlayerController = Instigator ? Cast<AAzurukPlayerController>(Instigator->Controller) : NULL;
	FVector FinalAim = FVector::ZeroVector;

	if (PlayerController)
	{
		FVector CamLoc;
		FRotator CamRot;
		PlayerController->GetPlayerViewPoint(CamLoc, CamRot);
		FinalAim = CamRot.Vector();
	}
	else if (Instigator)
	{
		FinalAim = Instigator->GetBaseAimRotation().Vector();
	}

	return FinalAim;
}

FVector AAzurukAbilityProjectile::GetAdjustedAim() const
{
	AAzurukPlayerController* const PlayerController = Instigator ? Cast<AAzurukPlayerController>(Instigator->Controller) : NULL;
	FVector FinalAim = FVector::ZeroVector;
	// If we have a player controller use it for the aim
	if (PlayerController)
	{
		FVector CamLoc;
		FRotator CamRot;
		PlayerController->GetPlayerViewPoint(CamLoc, CamRot);
		FinalAim = CamRot.Vector();
	}
	else if (Instigator)
	{
		// Now see if we have an AI controller - we will want to get the aim from there if we do
		AAzurukAIController* AIController = AbilityOwner ? Cast<AAzurukAIController>(AbilityOwner->Controller) : NULL;
		if (AIController != NULL)
		{
			FinalAim = AIController->GetControlRotation().Vector();
		}
		else
		{
			FinalAim = Instigator->GetBaseAimRotation().Vector();
		}
	}

	return FinalAim;
}

FVector AAzurukAbilityProjectile::GetCameraDamageStartLocation(const FVector& AimDir) const
{
	AAzurukPlayerController* PC = AbilityOwner ? Cast<AAzurukPlayerController>(AbilityOwner->Controller) : NULL;
	AAzurukAIController* AIPC = AbilityOwner ? Cast<AAzurukAIController>(AbilityOwner->Controller) : NULL;
	FVector OutStartTrace = FVector::ZeroVector;

	if (PC)
	{
		// use player's camera
		FRotator UnusedRot;
		PC->GetPlayerViewPoint(OutStartTrace, UnusedRot);

		// Adjust trace so there is nothing blocking the ray between the camera and the pawn, and calculate distance from adjusted start
		OutStartTrace = OutStartTrace + AimDir * ((Instigator->GetActorLocation() - OutStartTrace) | AimDir);
	}
	else if (AIPC)
	{
		OutStartTrace = GetAttachLocation();
	}

	return OutStartTrace;
}

FHitResult AAzurukAbilityProjectile::AbilityTrace(const FVector& StartTrace, const FVector& EndTrace) const
{
	static FName AbilityUseTag = FName(TEXT("AbilityTrace"));

	// Perform trace to retrieve hit info
	FCollisionQueryParams TraceParams(AbilityUseTag, true, Instigator);
	TraceParams.bTraceAsyncScene = true;
	TraceParams.bReturnPhysicalMaterial = true;

	FHitResult Hit(ForceInit);
	GetWorld()->LineTraceSingle(Hit, StartTrace, EndTrace, COLLISION_ABILITY, TraceParams);

	return Hit;
}
