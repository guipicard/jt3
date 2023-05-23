#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ReturnHomTrigger.generated.h"

class UBoxComponent;

UCLASS()
class MYPROJECT_API AReturnHomTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	AReturnHomTrigger();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* PlatformSceneRoot;
	
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* PlatformCollisionBox;

private:
	UFUNCTION(BlueprintCallable)
	void ActivateTrigger(AActor* OtherActor);

};
