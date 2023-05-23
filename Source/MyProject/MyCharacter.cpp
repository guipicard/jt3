#include "MyCharacter.h"
#include "Avatar.h"
#include "GameFramework/Character.h"

AMyCharacter::AMyCharacter()
	: m_Jumping(false)
	  , m_Crouched(false)
	  , m_Dead(false)
	  , m_Grounded(true)
	  , m_Slash(false)
	  , m_Shield(false)
	  , m_CanMove(true)
{
}

void AMyCharacter::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (!InputComponent) return;

	InputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);
	InputComponent->BindAxis("Look", this, &AMyCharacter::LookAt);

	InputComponent->BindAction("Crouch", IE_Pressed, this, &AMyCharacter::BeginCrouch);
	InputComponent->BindAction("Crouch", IE_Released, this, &AMyCharacter::EndCrouch);
	InputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::Jump);
	InputComponent->BindAction("Slash", IE_Pressed, this, &AMyCharacter::BeginSlash);
	InputComponent->BindAction("Shield", IE_Pressed, this, &AMyCharacter::BeginShield);
	InputComponent->BindAction("Shield", IE_Released, this, &AMyCharacter::EndShield);
	InputComponent->BindAction("Enter", IE_Pressed, this, &AMyCharacter::Enter);
	InputComponent->BindAction("Interact", IE_Pressed, this, &AMyCharacter::Pickup);
}

void AMyCharacter::BeginSlash()
{
	if (!m_Grounded) return;
	m_CanMove = false;
	m_Slash = true;
}

void AMyCharacter::EndSlash()
{
	m_Slash = false;
}

void AMyCharacter::BeginShield()
{
	if (!m_Grounded) return;
	m_CanMove = false;
	m_Shield = true;
}

void AMyCharacter::EndShield()
{
	m_CanMove = true;
	m_Shield = false;
}

inline void AMyCharacter::SetCanMove()
{
	m_CanMove = true;
}

void AMyCharacter::MoveForward(float axisValue)
{
	if (!m_CanMove) return;
	// Get pawn
	APawn* pawn = GetPawn();
	if (!pawn) return;

	if (pawn->GetVelocity() != FVector{0.0f, 0.0f, 0.0f})
	{
		m_Slash = false;
	}
	FVector forward = pawn->GetActorForwardVector();
	pawn->AddMovementInput(forward, axisValue);
}

void AMyCharacter::MoveRight(float axisValue)
{
	if (!m_CanMove) return;
	// Get pawn
	APawn* pawn = GetPawn();
	if (!pawn) return;

	FVector right = pawn->GetActorRightVector();
	pawn->AddMovementInput(right, axisValue);
}

void AMyCharacter::BeginCrouch()
{
	// Get pawn
	APawn* pawn = GetPawn();
	if (!pawn) return;

	// Case Pawn as Character
	ACharacter* character = Cast<ACharacter>(pawn);
	if (!character) return;

	m_Crouched = true;
	m_Slash = false;
	character->Crouch();
}

void AMyCharacter::EndCrouch()
{
	// Get pawn
	APawn* pawn = GetPawn();
	if (!pawn) return;

	// Case Pawn as Character
	ACharacter* character = Cast<ACharacter>(pawn);
	if (!character) return;

	m_Crouched = false;
	m_Slash = false;
	character->UnCrouch();
}

void AMyCharacter::LookAt(float axisValue)
{
	// Get delta time
	UWorld* world = GetWorld();
	if (!world) return;
	float dt = world->GetDeltaSeconds();

	// Get pawn and axis
	APawn* pawn = GetPawn();
	if (!pawn) return;
	float axis = rotationSpeed * axisValue * dt;

	pawn->AddControllerYawInput(axis);
}

void AMyCharacter::SetGrounded()
{
	m_Grounded = true;
	m_Jumping = false;
}

bool AMyCharacter::GetIsGrounded()
{
	return m_Grounded;
}

void AMyCharacter::Jump()
{
	if (!m_CanMove || !m_Grounded) return;
	// Get pawn
	APawn* pawn = GetPawn();
	if (!pawn) return;

	// Case Pawn as Character
	ACharacter* character = Cast<ACharacter>(pawn);
	if (!character) return;

	m_Jumping = true;
	character->Jump();
}

void AMyCharacter::SetDead()
{
	m_Dead = true;
	DisableInput(this);
}

void AMyCharacter::SetAlive()
{
	m_Dead = false;
	EnableInput(this);
}

void AMyCharacter::Enter()
{
	FTransform Transform = GetCharacter()->GetActorTransform();
	
	OnCharacterBeginLevel.Broadcast(Transform);
}

void AMyCharacter::PickupSubscribe(UBaseItem* _item)
{
	OnCharacterPickup.RemoveAll(this);
	PickupItem = _item;
	OnCharacterPickup.AddDynamic(_item, &UBaseItem::OnPickup);
}

void AMyCharacter::Pickup()
{
	if (PickupItem == nullptr) return;
	
	UGameInstance* inst = GetGameInstance();
	UMyGameInstance* DemoInst = Cast<UMyGameInstance>(inst);
	if (DemoInst == nullptr) return;
	
	OnCharacterPickup.Broadcast(DemoInst);
	OnCharacterPickup.Clear();

	PickupItem->m_Container->Destroy();
	PickupItem = nullptr;
	
}
