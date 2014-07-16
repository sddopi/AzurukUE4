

#pragma once

#include "AzurukSensingComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = AI, HideCategories = (Activation, "Components|Activation", Collision))
class UAzurukSensingComponent : public UActorComponent
{
	GENERATED_UCLASS_BODY()

public:

	/* See if there are interesting sounds and sights that we want to detect, and respond to them if so. 
	 * TODO: Give an array of targets
	 */
	virtual bool SensePawn(const class APawn* Other) const;

	/*
	* Chance of seeing other pawn decreases with increasing distance or angle in peripheral vision
	* @return true if the specified pawn Other is potentially visible (within peripheral vision, etc.) - still need to do LineOfSightTo() check to see if actually visible.
	*/
	virtual bool CouldSeePawn(const class APawn* Other) const;

	/* Sets PeripheralVisionAngle. Calculates PeripheralVisionCosine from PeripheralVisionAngle */
	virtual void SetPeripheralVisionAngle(const float NewPeripheralVisionAngle);

	/* Get position where hearing/seeing occurs (i.e. ear/eye position).  If we ever need different positions for hearing/seeing, we'll deal with that then! */
	virtual FVector GetSensorLocation() const;

protected:

	/* Maximum sight distance. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
	float SightRadius;

	/* How far to the side AI can see, in degrees. Use SetPeripheralVisionAngle to change the value at runtime. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AI)
	float PeripheralVisionAngle;

	/* Cosine of limits of peripheral vision. Computed from PeripheralVisionAngle. */
	UPROPERTY()
	float PeripheralVisionCosine;

	AController* GetSensorController() const; // Get the controller of the sensor actor.
	
};
