#include "Azuruk.h"
#include "AzurukGameMode.h"

AAzurukGameMode::AAzurukGameMode(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
}

APlayerController* AAzurukGameMode::Login(const FString& Portal, const FString& Options, const TSharedPtr<class FUniqueNetId>& UniqueId, FString& ErrorMessage)
{
	APlayerController* tController = Super::Login(Portal, Options, UniqueId, ErrorMessage);

	return tController;
}


