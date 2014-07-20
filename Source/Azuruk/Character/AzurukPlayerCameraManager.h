

#pragma once

#include "AzurukPlayerCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class AAzurukPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_UCLASS_BODY()

	/**  */
	virtual void UpdateCamera(float DeltaTime) override;
	void UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime) override;
};
