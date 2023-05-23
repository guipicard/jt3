#pragma once

#include "CoreMinimal.h"
#include "MyCharacter.h"
#include "Potion.generated.h"

UCLASS()
class MYPROJECT_API UPotion : public UBaseItem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	float HpRestored;
	
protected:
	virtual void Use(AActor* Actor) override;

private:
	
};
