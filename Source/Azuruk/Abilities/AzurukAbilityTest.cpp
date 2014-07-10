

#include "Azuruk.h"
#include "AzurukAbilityTest.h"


AAzurukAbilityTest::AAzurukAbilityTest(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

void AAzurukAbilityTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAzurukAbilityTest::Initialize(APawn* owner, APawn* instigator)
{
	Super::Initialize(owner, instigator);
}

void AAzurukAbilityTest::InputPressed()
{
	Super::InputPressed();
}

void AAzurukAbilityTest::InputReleased()
{
	Super::InputReleased();
}

FHitResult AAzurukAbilityTest::GetHitResult(float Range, FName StartSocket)
{
	const FVector Origin = GetCastingLocation(StartSocket);
	const FVector ShootDir = GetCameraAim();

	const FVector StartTrace = GetCameraDamageStarLocation(ShootDir);
	const FVector EndTrace = (StartTrace + ShootDir * Range);
	FHitResult Impact = RangedPowerTrace(StartTrace, EndTrace);

	DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Black, true, 10.0f, 0.0f, 1.0f);

	if (Impact.GetActor())
	{
		float impactLen;
		FVector impactDir;
		const FVector AdjustedDir = (Impact.ImpactPoint - Origin).SafeNormal();
		Impact.ImpactPoint.ToDirectionAndLength(impactDir, impactLen);
		FHitResult hitResult = RangedPowerTrace(Origin, Impact.ImpactPoint); //Origin + impactDir*range);
		DrawDebugLine(GetWorld(), Origin, Impact.ImpactPoint, FColor::Blue, true, 10.0f, 0.0f, 1.0f);

		if (hitResult.GetActor())
		{
			DrawDebugLine(GetWorld(), Origin, Impact.ImpactPoint, FColor::Red, true, 10.0f, 0.0f, 1.0f);
			return hitResult;
		}
		return Impact;
	}
	return Impact;
}

AActor* AAzurukAbilityTest::GetActorHit(float Range, FName StartSocket)
{
	FVector Origin = GetCastingLocation(StartSocket);
	const FVector ShootDir = GetCameraAim();

	FVector StartTrace = GetCameraDamageStarLocation(ShootDir);
	const FVector EndTrace = (StartTrace + ShootDir * Range);
	FHitResult Impact = RangedPowerTrace(StartTrace, EndTrace);

	DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Black, true, 10.0f, 0.0f, 1.0f);

	if (Impact.GetActor())
	{
		float impactLen;
		FVector impactDir;
		const FVector AdjustedDir = (Impact.ImpactPoint - Origin).SafeNormal();
		Impact.ImpactPoint.ToDirectionAndLength(impactDir, impactLen);
		FHitResult hitResult = RangedPowerTrace(Origin, Impact.ImpactPoint); //Origin + impactDir*range);
		DrawDebugLine(GetWorld(), Origin, Impact.ImpactPoint, FColor::Blue, true, 10.0f, 0.0f, 1.0f);

		if (hitResult.GetActor())
		{
			DrawDebugLine(GetWorld(), Origin, Impact.ImpactPoint, FColor::Red, true, 10.0f, 0.0f, 1.0f);
			return hitResult.GetActor();
		}
		return Impact.GetActor();
	}
	return nullptr;
}

void AAzurukAbilityTest::SpawnTrailEffect(UParticleSystem* trailFX, float trailSpeed, FName trailSpeedParam, FHitResult target, FName SocketName)
{
	FVector Origin = GetCastingLocation(SocketName);
	if (target.GetActor())
	{
		if (trailFX)
		{
			UParticleSystemComponent* TrailPSC = UGameplayStatics::SpawnEmitterAtLocation(AbilityOwner, trailFX, Origin);
			if (TrailPSC)
			{
				const FVector AdjustedDir = (target.ImpactPoint - Origin).SafeNormal();
				FVector ParticleSpeed = AdjustedDir * trailSpeed;
				TrailPSC->SetVectorParameter(trailSpeedParam, ParticleSpeed);
			}
		}
	}
}

FVector AAzurukAbilityTest::GetCameraDamageStarLocation(const FVector& AimDir) const
{
	FVector OutStartTrace = FVector::ZeroVector;
	if (Instigator)
	{
		FRotator UnusedRot;
		//Instigator->GetPlayerViewPoint(OutStartTrace, UnusedRot);
		OutStartTrace = OutStartTrace + AimDir * ((AbilityOwner->GetActorLocation() - OutStartTrace) | AimDir);
		//OutStartTrace = OutStartTrace + AimDir * ((Instigator->GetActorLocation() - OutStartTrace));
	}
	return OutStartTrace;
}

FVector AAzurukAbilityTest::GetCameraAim() const
{
	FVector FinalAim = FVector::ZeroVector;

	if (Instigator)
	{
		FVector CamLoc;
		FRotator CamRot;
		//Instigator->GetPlayerViewPoint(CamLoc, CamRot);
		FinalAim = CamRot.Vector();
	}
	else if (AbilityOwner)
	{
		FinalAim = AbilityOwner->GetBaseAimRotation().Vector();
	}
	return FinalAim;
}

FVector AAzurukAbilityTest::GetCastingLocation(FName SocketName) const
{
	// Get socket location
	if (false)
	{
		// Return socket location
	}
	return FVector(0, 0, 0);
}

FHitResult AAzurukAbilityTest::RangedPowerTrace(const FVector& StartTrace, const FVector& EndTrace) const
{
	FHitResult Hit(ForceInit);

	static FName PowerTag = FName(TEXT("PowerTrace"));
	FCollisionQueryParams TraceParams(PowerTag, false, AbilityOwner);
	TraceParams.bTraceComplex = false;
	TraceParams.bTraceAsyncScene = false;
	TraceParams.bReturnPhysicalMaterial = true;

	bool traceResult = GetWorld()->LineTraceSingle(Hit, StartTrace, EndTrace, ECollisionChannel::ECC_WorldDynamic, TraceParams);

	return Hit;
}