

#pragma once

#include "GameFramework/HUD.h"
#include "AzurukHUD.generated.h"

/**
 * 
 */
UCLASS()
class AAzurukHUD : public AHUD
{
	GENERATED_UCLASS_BODY()

	/* Main HUD update loop. */
	virtual void DrawHUD() OVERRIDE;

	/* Texture for HUD elements. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Azuruk HUD")
	UTexture2D* HUDHealthAssets;

protected:

	/* Floor for automatic hud scaling. */
	static const float MinHudScale;

	/* UI scaling factor for other resolutions than Full HD. */
	float ScaleUI;

	/* General offset for HUD elements. */
	float Offset;

	/* Health bar background icon. */
	UPROPERTY()
	FCanvasIcon HealthBarBg;

	/* Health bar icon. */
	UPROPERTY()
	FCanvasIcon HealthBar;

	/* Health icon on the health bar. */
	UPROPERTY()
	FCanvasIcon HealthIcon;

	/* Draw player's health bar. */
	void DrawHealth();

	void MakeUV(FCanvasIcon&, FVector2D&, FVector2D&, uint16, uint16, uint16, uint16);
	
};
