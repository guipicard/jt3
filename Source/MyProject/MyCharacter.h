#pragma once

#include "CoreMinimal.h"
#include "MyGameInstance.h"
#include "GameFramework/PlayerController.h"
#include "MyCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBeginLevel, FTransform, Transform);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPickupItem, UMyGameInstance*, GameInstance);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUseItem);

UCLASS()
class MYPROJECT_API AMyCharacter : public APlayerController
{
	GENERATED_BODY()

public:
	AMyCharacter();

	virtual void SetupInputComponent() override;

	FBeginLevel OnCharacterBeginLevel;
	FPickupItem OnCharacterPickup;
	FUseItem OnUseItem;

	UPROPERTY(EditAnywhere)
	float rotationSpeed = 80.0f;
	
	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe), Category = "Character")
	void SetDead();
	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe), Category = "Character")
	void SetAlive();

	bool IsCrouched() { return m_Crouched; }
	bool IsJumping() { return m_Jumping; }

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe), Category = "Character")
	void SetGrounded();

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Character")
	bool GetIsGrounded();
	
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Character")
	bool IsDead() { return m_Dead; }

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Character")
	bool IsSlashing() const { return m_Slash; }
	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe), Category = "Character")
	void EndSlash();
	
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Character")
	bool IsShielding() const { return m_Shield; }

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe), Category = "Character")
	void SetCanMove();
	
	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe), Category = "Character")
	void PickupSubscribe(UBaseItem* _item);

	UPROPERTY(BlueprintReadWrite)
	AActor* m_Target;

	float playerHp;
	
private:
	void MoveForward(float axisValue);
	void MoveRight(float axisValue);
	void BeginCrouch();
	void EndCrouch();
	void LookAt(float axisValue);
	void Jump();
	
	void BeginSlash();
	void BeginShield();
	void EndShield();
	void Enter();
	void Pickup();

	UBaseItem* PickupItem;

	bool m_Jumping;
	bool m_Crouched;
	bool m_Dead;
	bool m_Grounded;
	bool m_Slash;
	bool m_Shield;
	bool m_CanMove;
};
