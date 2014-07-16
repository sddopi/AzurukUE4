

#include "Azuruk.h"
#include "AzurukSensingComponent.h"


UAzurukSensingComponent::UAzurukSensingComponent(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	SightRadius = 5000.0f;
	PeripheralVisionAngle = 90.0f;
	PeripheralVisionCosine = FMath::Cos(FMath::DegreesToRadians(PeripheralVisionAngle));
}

bool UAzurukSensingComponent::SensePawn(const class APawn* Other) const
{
	if (CouldSeePawn(Other))
	{
		if (GetSensorController()->LineOfSightTo(Other, GetSensorLocation(), true))
		{
			return true;
		}
	}
	return false;
}

bool UAzurukSensingComponent::CouldSeePawn(const class APawn* Other) const
{
	if (!Other)
	{
		return false;
	}
	
	FVector const otherPos = Other->GetActorLocation();
	FVector const selfPos = GetSensorLocation();
	FVector const selfToOther = otherPos - selfPos;
	
	float const selfToOtherSqrd = selfToOther.SizeSquared();
	
	if (selfToOtherSqrd > FMath::Square(SightRadius))
	{
		return false;
	}
	
	FVector const selfToOtherDir = selfToOther.SafeNormal();
	FVector const facingDir = GetOwner()->GetActorRotation().Vector();
	
	return ((selfToOtherDir | facingDir) >= PeripheralVisionCosine);
}

void UAzurukSensingComponent::SetPeripheralVisionAngle(const float NewPeripheralVisionAngle)
{
	PeripheralVisionAngle = NewPeripheralVisionAngle;
	PeripheralVisionCosine = FMath::Cos(FMath::DegreesToRadians(PeripheralVisionAngle));
}

FVector UAzurukSensingComponent::GetSensorLocation() const
{
	FVector SensorLoc(FVector::ZeroVector);
	const APawn* SensorPawn = Cast<APawn>(GetOwner());

	if (SensorPawn)
	{
		SensorLoc = SensorPawn->GetPawnViewLocation();
	}
	return SensorLoc;
}

AController* UAzurukSensingComponent::GetSensorController() const
{
	const APawn* SensorPawn = Cast<APawn>(GetOwner());

	if (SensorPawn)
	{
		return SensorPawn->Controller;
	}
	return NULL;
}




