

#pragma once

#include "GameFramework/Actor.h"
#include "AzurukAbilityManager.generated.h"

/**
 * Ability manager
 */
UCLASS()
class UAzurukAbilityManager : public UActorComponent
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability|Manager")
	TArray<class UAzurukAbilityBase*> AbilityList;

	/* Debug method */
	UFUNCTION(BlueprintCallable, Category = "Ability|Manager")
	void AddPower(TSubclassOf<class UAzurukAbilityBase> ability, APawn* Owner);
	
public:
	class UAzurukAbilityBase* GetButtonOne();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Ability")
	class UAzurukAbilityBase* AbilityButtonOneObj;

};
