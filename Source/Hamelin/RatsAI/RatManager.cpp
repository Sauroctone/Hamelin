// Fill out your copyright notice in the Description page of Project Settings.

#include "RatManager.h"
#include "RatsAI/RatCharacter.h"
#include "RatsAI/RatAIController.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Engine.h"


// Sets default values
ARatManager::ARatManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ARatManager::Debug()
{
	if (SpawnTarget->IsValidLowLevel())
	{
		CreateRat(SpawnTarget);
		GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Yellow, "RATS !");
	}
}

// Called when the game starts or when spawned
void ARatManager::BeginPlay()
{
	Super::BeginPlay();
	Debug();
}

void ARatManager::CreateRat(AActor* TargetPoint)
{
	FActorSpawnParameters SpawnInfo;
	ACharacter* RatCharacter = GetWorld()->SpawnActor<ARatCharacter>(TargetPoint->GetActorLocation(), TargetPoint->GetActorRotation(), SpawnInfo);
	ARatAIController* RatController = NewObject<ARatAIController>(this);
	RatController->Possess(RatCharacter);

	DanglingRats.Add(RatController);
}

void ARatManager::DestroyRat(ARatAIController* DestroyedRat)
{
	
}

// Called every frame
void ARatManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

