

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
		// Draw Vitals Background
		Canvas->DrawIcon(VitalsBack.HUDComponent, (Canvas->ClipX + VitalsBack.xPosition * ScaleUI) / 2, (Canvas->ClipY + VitalsBack.yPosition * ScaleUI) / 2, ScaleUI);
		// Draw Health Bar
		DrawHealth();
		// Draw Morph Bar One
		DrawMorphBarOne();
		// Draw Morph Bar Two
		DrawMorphBarTwo();
	}
}

void AAzurukHUD::DrawHealth()
{
	// Get Player Pawn
	AAzurukPlayerCharacter* MyPawn = Cast<AAzurukPlayerCharacter>(GetOwningPawn());
	// Get Player Health Scale Amount
	const float HealthAmount = FMath::Min(1.0f, MyPawn->GetHealth() / MyPawn->GetMaxHealth());
	// Set Default Positions
	const float PosX = (Canvas->ClipX + HealthBarBack.xPosition * ScaleUI) / 2;
	const float PosY = (Canvas->ClipY + HealthBarBack.yPosition * ScaleUI) / 2;
	// Draw Health Background
	Canvas->DrawIcon(HealthBarBack.HUDComponent, PosX, PosY, ScaleUI);
	// Draw Health Bar
	FCanvasTileItem TileItem(FVector2D(PosX + HealthBar.xPosition * ScaleUI, PosY + HealthBar.yPosition * ScaleUI),
							 HealthBar.HUDComponent.Texture->Resource, 
							 FVector2D(HealthBar.HUDComponent.UL * HealthAmount * ScaleUI, HealthBar.HUDComponent.VL * ScaleUI), 
							 FLinearColor::White);
	MakeUV(HealthBar.HUDComponent, TileItem.UV0, TileItem.UV1, 
		   HealthBar.HUDComponent.U, HealthBar.HUDComponent.V, 
		   HealthBar.HUDComponent.UL * HealthAmount, HealthBar.HUDComponent.VL);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(TileItem);
	// Draw Health Icon
	Canvas->DrawIcon(HealthIcon.HUDComponent, PosX + HealthIcon.xPosition * ScaleUI, PosY + HealthIcon.yPosition * ScaleUI, ScaleUI);
}

void AAzurukHUD::DrawMorphBarOne()
{
	// Get Player Pawn
	AAzurukPlayerCharacter* MyPawn = Cast<AAzurukPlayerCharacter>(GetOwningPawn());
	
	const float MorphAmount = MyPawn->MorphComp->ReturnMorph(EFeatureName::FeatureOne) ?
		MyPawn->MorphComp->ReturnMorph(EFeatureName::FeatureOne)->ReturnMorphPercent() :
		0.0f;
	// Set Default Positions
	const float PosX = (Canvas->ClipX + MorphBarBack_One.xPosition * ScaleUI) / 2;
	const float PosY = (Canvas->ClipY + MorphBarBack_One.yPosition * ScaleUI) / 2;
	// Draw Morph Background
	Canvas->DrawIcon(MorphBarBack_One.HUDComponent, PosX, PosY, ScaleUI);
	// Draw Morph Bar
	FCanvasTileItem TileItem(FVector2D(PosX + MorphBar_One.xPosition * ScaleUI, PosY + MorphBar_One.yPosition * ScaleUI),
							 MorphBar_One.HUDComponent.Texture->Resource,
							 FVector2D(MorphBar_One.HUDComponent.UL * MorphAmount * ScaleUI, MorphBar_One.HUDComponent.VL * ScaleUI),
							 FLinearColor::White);
	MakeUV(MorphBar_One.HUDComponent, TileItem.UV0, TileItem.UV1,
		   MorphBar_One.HUDComponent.U, MorphBar_One.HUDComponent.V,
		   MorphBar_One.HUDComponent.UL * MorphAmount, MorphBar_One.HUDComponent.VL);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(TileItem);
}

void AAzurukHUD::DrawMorphBarTwo()
{
	// Get Player Pawn
	AAzurukPlayerCharacter* MyPawn = Cast<AAzurukPlayerCharacter>(GetOwningPawn());
	// Get Morph One Scale Amount
	const float MorphAmount = MyPawn->MorphComp->ReturnMorph(EFeatureName::FeatureTwo) ?
		MyPawn->MorphComp->ReturnMorph(EFeatureName::FeatureTwo)->ReturnMorphPercent() :
		0.0f;
	// Set Default Positions
	const float PosX = (Canvas->ClipX + MorphBarBack_Two.xPosition * ScaleUI) / 2;
	const float PosY = (Canvas->ClipY + MorphBarBack_Two.yPosition * ScaleUI) / 2;
	// Draw Morph Background
	Canvas->DrawIcon(MorphBarBack_Two.HUDComponent, PosX, PosY, ScaleUI);
	// Draw Morph Bar
	FCanvasTileItem TileItem(FVector2D(PosX + MorphBar_Two.xPosition * ScaleUI, PosY + MorphBar_Two.yPosition * ScaleUI),
							 MorphBar_Two.HUDComponent.Texture->Resource,
							 FVector2D(MorphBar_Two.HUDComponent.UL * MorphAmount * ScaleUI, MorphBar_Two.HUDComponent.VL * ScaleUI),
							 FLinearColor::White);
	MakeUV(MorphBar_Two.HUDComponent, TileItem.UV0, TileItem.UV1,
		   MorphBar_Two.HUDComponent.U, MorphBar_Two.HUDComponent.V,
		   MorphBar_Two.HUDComponent.UL * MorphAmount, MorphBar_Two.HUDComponent.VL);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(TileItem);
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


