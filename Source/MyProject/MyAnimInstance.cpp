#include "MyAnimInstance.h"

#include "MyCharacter.h"
#include "GameFramework/Character.h"

float UMyAnimInstance::GetCharacterDirection() const
{
	APawn* pawn = TryGetPawnOwner();
	if (!pawn) return 0.0f;

	FVector velocity = pawn->GetVelocity();
	if (velocity.IsNearlyZero()) return 0.0f;

	FVector forward = pawn->GetActorForwardVector();
	FVector right = pawn->GetActorRightVector();

	float forwardSpeed = FVector::DotProduct(velocity, forward);
	float strafingSpeed = FVector::DotProduct(velocity, right);

	float directionAngle = FMath::Atan2(strafingSpeed, forwardSpeed) * (180.0f / PI);

	return directionAngle;
}

float UMyAnimInstance::GetCharacterSpeed() const
{
	APawn* pawn = TryGetPawnOwner();
	if (!pawn) return 0.0f;

	FVector velocity = pawn->GetVelocity();
	return velocity.Size();
}

bool UMyAnimInstance::GetIsPawnCrouching()
{
	APawn* pawn = TryGetPawnOwner();
	if (!pawn) return false;

	AMyCharacter* MyController = Cast<AMyCharacter>(pawn->GetController());
	if (!MyController) return false;
	
	return MyController->IsCrouched();
}

bool UMyAnimInstance::GetIsJumping()
{
	APawn* Pawn = TryGetPawnOwner();
	if (Pawn)
	{
		AMyCharacter* MyController = Cast<AMyCharacter>(Pawn->GetController());
		if (MyController)
		{
			return MyController->IsJumping();
		}
	}
	return false;
}

void UMyAnimInstance::IsGrounded()
{
	APawn* Pawn = TryGetPawnOwner();
	if (Pawn)
	{
		AMyCharacter* MyController = Cast<AMyCharacter>(Pawn->GetController());
		if (MyController)
		{
			MyController->SetGrounded();
		}
	}
}

bool UMyAnimInstance::GetIsGrounded()
{
	APawn* Pawn = TryGetPawnOwner();
	if (Pawn)
	{
		AMyCharacter* MyController = Cast<AMyCharacter>(Pawn->GetController());
		if (MyController)
		{
			return MyController->GetIsGrounded();
		}
	}
	return false; 
}

bool UMyAnimInstance::GetIsSlashing()
{
	APawn* Pawn = TryGetPawnOwner();
	if (Pawn)
	{
		AMyCharacter* MyController = Cast<AMyCharacter>(Pawn->GetController());
		if (MyController)
		{
			return MyController->IsSlashing();
		}
	}
	return false;
}

bool UMyAnimInstance::GetIsShielding()
{
	APawn* Pawn = TryGetPawnOwner();
	if (Pawn)
	{
		AMyCharacter* MyController = Cast<AMyCharacter>(Pawn->GetController());
		if (MyController)
		{
			return MyController->IsShielding();
		}
	}
	return false;
}

bool UMyAnimInstance::IsDead()
{
	APawn* Pawn = TryGetPawnOwner();
	if (Pawn)
	{
		AMyCharacter* MyController = Cast<AMyCharacter>(Pawn->GetController());
		if (MyController)
		{
			return MyController->IsDead();
		}
	}
	return false;
}

// bool UMyAnimInstance::GetIsFalling()
// {
// 	APawn* Pawn = TryGetPawnOwner();
// 	if (Pawn)
// 	{
// 		AMyCharacter* erikaController = Cast<AMyCharacter>(Pawn->GetController());
// 		if (erikaController)
// 		{
// 			return erikaController->SetIsFalling();
// 		}
// 	}
// 	return false;
// }

// bool UMyAnimInstance::GetIsPawnDancing()
// {
// 	APawn* pawn = TryGetPawnOwner();
// 	if (pawn)
// 	{
// 		AMyCharacter* erikaController = Cast<AMyCharacter>(pawn->GetController());
// 		if (erikaController)
// 		{
// 			return erikaController->IsDancing();
// 		}
// 	}
// 	return false;
// }
