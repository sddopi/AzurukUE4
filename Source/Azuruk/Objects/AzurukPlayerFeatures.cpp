

#include "Azuruk.h"
#include "AzurukPlayerFeatures.h"

UAzurukPlayerFeatures::UAzurukPlayerFeatures(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	UAzurukMorphingComponent* OwnerComp = Cast<UAzurukMorphingComponent>(GetOuter());

	if (OwnerComp)
	{
		maxmorphTime = OwnerComp->defaultMorphTime;
		morphTime = maxmorphTime;
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

void UAzurukPlayerFeatures::SetMorphTimer(class AAzurukPlayerCharacter* MorphOwner, float TimerInterval, bool Active)
{
	if (MorphOwner)
	{
		MorphOwner->GetWorldTimerManager().SetTimer(this, &UAzurukPlayerFeatures::ModifyMorphTime, TimerInterval, true);
	}
}

void UAzurukPlayerFeatures::ModifyMorphTime()
{

	if (morphTime == 0.f)
	{

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