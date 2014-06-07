#pragma once

#include "GameFramework/GameMode.h"
#include "AzurukGameMode.generated.h"

/**
 * 
 */
UCLASS(minimalapi)
class AAzurukGameMode : public AGameMode
{
	GENERATED_UCLASS_BODY()	

protected:

	/*TSet<AzurukCharacterFeatures, FeatureCompare> FeatureContainer;*/

	/*
	* Returns Player Controller if Login successful
	*
	* Added Character Features Set Population
	*/
	virtual APlayerController* Login(const FString& Portal, const FString& Options, const TSharedPtr<class FUniqueNetId>& UniqueId, FString& ErrorMessage) OVERRIDE;
};
