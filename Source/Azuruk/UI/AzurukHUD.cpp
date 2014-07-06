

#include "Azuruk.h"
#include "AzurukHUD.h"

const float AAzurukHUD::MinHudScale = 0.5f;

AAzurukHUD::AAzurukHUD(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	Offset = 20.0f;
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
	}
	
}

void AAzurukHUD::DrawHealth()
{
	AAzurukPlayerCharacter* MyPawn = Cast<AAzurukPlayerCharacter>(GetOwningPawn());
	Canvas->SetDrawColor(FColor::White);
	const float HealthPosX = (Canvas->ClipX + HealthBarBack.UL) / 2;
	const float HealthPosY = (Canvas->ClipY / 2) - (Offset + HealthBarBack.VL) * ScaleUI;
	Canvas->DrawIcon(HealthBarBack, HealthPosX, HealthPosY, ScaleUI);
	const float HealthAmount = FMath::Min(1.0f, MyPawn->Health / MyPawn->GetMaxHealth());

	FCanvasTileItem TileItem(FVector2D(HealthPosX, HealthPosY), HealthBar.Texture->Resource, FVector2D(HealthBar.UL * HealthAmount  * ScaleUI, HealthBar.VL * ScaleUI), FLinearColor::Red);
	MakeUV(HealthBar, TileItem.UV0, TileItem.UV1, HealthBar.U, HealthBar.V, HealthBar.UL * HealthAmount, HealthBar.VL);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(TileItem);

	Canvas->DrawIcon(HealthIcon, HealthPosX + Offset * ScaleUI, HealthPosY + (HealthBar.VL - HealthIcon.VL) / 2.0f * ScaleUI, ScaleUI);
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


