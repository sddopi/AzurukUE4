

#include "Azuruk.h"
#include "AzurukHUD.h"

const float AAzurukHUD::MinHudScale = 0.5f;

AAzurukHUD::AAzurukHUD(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
}

void AAzurukHUD::DrawHUD()
{
	Super::DrawHUD();

	AAzurukPlayerCharacter* MyPawn = Cast<AAzurukPlayerCharacter>(GetOwningPawn());

	ScaleUI = Canvas->ClipY / 1080.0f;

	// enforce min
	ScaleUI = FMath::Max(ScaleUI, MinHudScale);


	if (MyPawn && MyPawn->IsAlive())
	{
		DrawHealth();
		DrawMorphBar();
	}
	
}

void AAzurukHUD::DrawHealth()
{
	AAzurukPlayerCharacter* MyPawn = Cast<AAzurukPlayerCharacter>(GetOwningPawn());
	Canvas->SetDrawColor(FColor::White);
	const float HealthPosX = (Canvas->ClipX + HealthBarBack.xPosition * ScaleUI);
	const float HealthPosY = (Canvas->ClipY + HealthBarBack.yPosition * ScaleUI);
	// Draw Health Background
	Canvas->DrawIcon(HealthBarBack.HUDComponent, HealthPosX, HealthPosY, ScaleUI);
	const float HealthAmount = FMath::Min(1.0f, MyPawn->GetHealth() / MyPawn->GetMaxHealth());
	// Draw Health Bar
	FCanvasTileItem TileItem(FVector2D(HealthPosX, HealthPosY), HealthBar.HUDComponent.Texture->Resource, FVector2D(HealthBar.HUDComponent.UL * HealthAmount  * ScaleUI, HealthBar.HUDComponent.VL * ScaleUI), FLinearColor::White);
	MakeUV(HealthBar.HUDComponent, TileItem.UV0, TileItem.UV1, HealthBar.HUDComponent.U, HealthBar.HUDComponent.V, HealthBar.HUDComponent.UL * HealthAmount, HealthBar.HUDComponent.VL);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(TileItem);
	// Draw Health Icon
	Canvas->DrawIcon(HealthIcon.HUDComponent, (HealthPosX + HealthIcon.xPosition), (HealthPosY + HealthIcon.yPosition), ScaleUI);
}

void AAzurukHUD::DrawMorphBar()
{
}

void AAzurukHUD::MakeUV(FCanvasIcon& Icon, FVector2D& UV0, FVector2D& UV1, uint16 U, uint16 V, uint16 UL, uint16 VL)
{
	if (Icon.Texture)
	{
		const float Width = Icon.Texture->GetSurfaceWidth();
		const float Height = Icon.Texture->GetSurfaceHeight();
		UV0 = FVector2D(U / Width, V / Height);
		UV1 = UV0 + FVector2D(UL / Width, VL / Height);
	}
}


