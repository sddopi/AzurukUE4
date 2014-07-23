

#include "Azuruk.h"
#include "AzurukPlayerFeatures.h"

UAzurukPlayerFeatures::UAzurukPlayerFeatures(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	OwnerComp = Cast<UAzurukMorphingComponent>(GetOuter());

	if (OwnerComp)
	{
		morphTimeMultiplier = OwnerComp->morphTimeMultiplier;
		maxmorphTime = OwnerComp->defaultMorphTime;
		morphTime = maxmorphTime;
		morphActive = false;
	}
}

void UAzurukPlayerFeatures::SetMorphFeatures(UAzurukCharacterFeatures* otherFeatures)
{
	morphSkelMesh = otherFeatures->featureSkelMesh;
	morphAnimInstance = otherFeatures->featureAnimInstance;
	morphMorphAnim = otherFeatures->featureMorphAnim;
}

void UAzurukPlayerFeatures::PassCharacterFeatures(class AAzurukPlayerCharacter* MorphOwner)
{
	MorphOwner->Mesh->SetSkeletalMesh(morphSkelMesh);
	MorphOwner->Mesh->SetAnimInstanceClass(morphAnimInstance);
	MorphOwner->SetMorphAnim(morphMorphAnim);
}

void UAzurukPlayerFeatures::SetMorphTimer(class AAzurukPlayerCharacter* MorphOwner, float TimerInterval)
{
	if (MorphOwner)
	{
		MorphOwner->GetWorldTimerManager().SetTimer(this, &UAzurukPlayerFeatures::ModifyMorphTime, TimerInterval, true);
	}
}

void UAzurukPlayerFeatures::ModifyMorphTime()
{
	morphTime = morphActive ?
		FMath::Max(morphTime - morphTimeMultiplier, 0.f) :
		FMath::Min(morphTime + morphTimeMultiplier, maxmorphTime);

	if (morphTime == 0.f)
	{
		morphActive = false;
		OwnerComp->ReturnAzurukOwner()->StartMorph(EFeatureName::FeatureDefault, true);
	}
	else if (morphTime == maxmorphTime)
	{
		SetMorphTimer(OwnerComp->ReturnAzurukOwner(), 0.f);
	}
}

float UAzurukPlayerFeatures::ReturnMorphPercent()
{
	return morphTime / maxmorphTime;
}

bool operator ==(UAzurukPlayerFeatures& LHS, UAzurukCharacterFeatures& RHS)
{
	return LHS.morphSkelMesh == RHS.featureSkelMesh &&
		LHS.morphAnimInstance == RHS.featureAnimInstance &&
		LHS.morphMorphAnim == RHS.featureMorphAnim;
}

UAzurukPlayerFeatures& UAzurukPlayerFeatures::operator =(UAzurukCharacterFeatures& other)
{
	morphSkelMesh = other.featureSkelMesh;
	morphAnimInstance = other.featureAnimInstance;
	morphMorphAnim = other.featureMorphAnim;

	return *this;
}