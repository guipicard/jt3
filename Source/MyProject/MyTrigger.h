#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyTrigger.generated.h"

class UBoxComponent;

UCLASS()
class MYPROJECT_API AMyTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	AMyTrigger();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* SceneRoot;
	
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* CollisionBox;

private:
	bool bActivated;

	UFUNCTION(BlueprintCallable)
	void ActivateTrigger(AActor* OtherActor);

	UFUNCTION(BlueprintCallable)
	void DeactivateTrigger(AActor* OtherActor); 

	FVector actorPosition;

	UFUNCTION(BlueprintCallable)
	void DoActivate(FTransform Transform);
};
