#include "Potion.h"
#include "Avatar.h"

void UPotion::Use(AActor* Actor)
{
	Super::Use(Actor);

	AAvatar* Avatar = Cast<AAvatar>(Actor);
	if (!Avatar) return;

	Avatar->Heal(HpRestored);
}
