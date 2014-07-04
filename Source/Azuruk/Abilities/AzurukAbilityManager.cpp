

#include "Azuruk.h"
#include "AzurukAbilityManager.h"
#include "AzurukAbilityBase.h"


UAzurukAbilityManager::UAzurukAbilityManager(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

void UAzurukAbilityManager::AddPower(TSubclassOf<UAzurukAbilityBase> ability, APawn* Owner)
{
	if (ability && Owner)
	{
		UAzurukAbilityBase* abilityObj = ConstructObject<UAzurukAbilityBase>(ability);

		abilityObj->Initialize(Owner, Owner->Controller);
		AbilityList.AddUnique(abilityObj);

		if (!AbilityButtonOneObj)
		{
			AbilityButtonOneObj = abilityObj;
		}
	}
}

UAzurukAbilityBase* UAzurukAbilityManager::GetButtonOne()
{
	if (AbilityButtonOneObj)
	{
		return AbilityButtonOneObj;
	}
	return NULL;
}