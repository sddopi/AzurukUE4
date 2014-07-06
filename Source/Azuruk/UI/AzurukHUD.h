

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

	/* GetHealth() Bar Icons */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GetHealth() HUD")
		FCanvasIcon HealthBarBack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GetHealth() HUD")
		FCanvasIcon HealthBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GetHealth() HUD")
		FCanvasIcon HealthIcon;

	/* Morph Bar Icons */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Morph HUD")
		FCanvasIcon MorphBarBack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Morph HUD")
		FCanvasIcon MorphBar;

protected:

	/* Floor for automatic hud scaling. */
	static const float MinHudScale;

	/* UI scaling factor for other resolutions than Full HD. */
	float ScaleUI;

	/* General offset for HUD elements. */
	float Offset;

	/* Draw player's health bar. */
	void DrawHealth();

	/* Draw player's morph bars */
	void DrawMorphBar();

	void MakeUV(FCanvasIcon&, FVector2D&, FVector2D&, uint16, uint16, uint16, uint16);
	
};
