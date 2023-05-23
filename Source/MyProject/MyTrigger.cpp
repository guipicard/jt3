// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTrigger.h"

#include "MyGameInstance.h"
#include "MyCharacter.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"


AMyTrigger::AMyTrigger()
{
	PrimaryActorTick.bCanEverTick = false;
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(SceneRoot);
}

void AMyTrigger::BeginPlay()
{
	Super::BeginPlay();
}

void AMyTrigger::ActivateTrigger(AActor* OtherActor)
{
	if (!OtherActor) return;

	APawn* ThePawn = Cast<APawn>(OtherActor);

	if (!ThePawn) return;

	AMyCharacter* TheController = Cast<AMyCharacter>(ThePawn->GetController());

	if (!TheController) return;

	bActivated = true;

	UGameInstance* inst = GetGameInstance();
	UMyGameInstance* DemoInst = Cast<UMyGameInstance>(inst);
	if (DemoInst == nullptr) return;
	
	if (!DemoInst->IsQuestCompleted())
	{
		TheController->OnCharacterBeginLevel.AddDynamic(this, &AMyTrigger::DoActivate);
	}
}


void AMyTrigger::DeactivateTrigger(AActor* OtherActor)
{
	if (!OtherActor) return;

	bActivated = false;

	APawn* ThePawn = Cast<APawn>(OtherActor);

	if (!ThePawn) return;

	AMyCharacter* TheController = Cast<AMyCharacter>(ThePawn->GetController());
	if (!TheController) return;

	TheController->OnCharacterBeginLevel.RemoveAll(this);
}

void AMyTrigger::DoActivate(FTransform Transform)
{
	if (!bActivated) return;

	UGameInstance* inst = GetGameInstance();
	UMyGameInstance* DemoInst = Cast<UMyGameInstance>(inst);
	if (DemoInst == nullptr) return;
	
	DemoInst->SetPlayerTransformBeforeQuest(Transform);

	UGameplayStatics::OpenLevel(GetWorld(), "W_Combat");
}
