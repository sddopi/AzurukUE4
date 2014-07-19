

#pragma once

#include "Engine.h"
#include "ParticleDefinitions.h"
#include "SoundDefinitions.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/Actor.h"
#include "Abilities/AzurukAbilityBase.h"
#include "Character/AzurukCharacterFeatures.h"
#include "Character/AzurukBaseCharacter.h"
#include "Character/AzurukPlayerCharacter.h"
#include "Character/AzurukAICharacter.h"
#include "Controllers/AzurukAIController.h"
#include "Controllers/AzurukPlayerController.h"
#include "Effects/AzurukEffectBase.h"


/** when you modify this, please note that this information can be saved with instances
* also DefaultEngine.ini [/Script/Engine.CollisionProfile] should match with this list **/
#define COLLISION_ABILITY		ECC_GameTraceChannel2
#define COLLISION_PROJECTILE	ECC_GameTraceChannel3
#define COLLISION_PIKCUP		ECC_GameTraceChannel4

DECLARE_LOG_CATEGORY_EXTERN(TempLog, Log, All);