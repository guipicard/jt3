#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

UCLASS()
class MYPROJECT_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe), Category = "Character")
	float GetCharacterDirection() const;

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe), Category = "Character")
	float GetCharacterSpeed() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Character")
	bool GetIsPawnCrouching();

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Character")
	bool GetIsJumping();

	UFUNCTION(BlueprintCallable)
	void IsGrounded();

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Character")
	bool GetIsGrounded();

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Character")
	bool GetIsSlashing();

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Character")
	bool GetIsShielding();
	
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Character")
	bool IsDead();
	
};