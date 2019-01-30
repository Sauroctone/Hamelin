// Fill out your copyright notice in the Description page of Project Settings.

#include "RatManager.h"
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
	
}

// Called when the game starts or when spawned
void ARatManager::BeginPlay()
{
	Super::BeginPlay();
}

void ARatManager::CreateRat(AActor* TargetPoint)
{
	//Spawn RatCharacterBP and store a reference to it's RatAIController (Autopossessed when spawned)
	FActorSpawnParameters SpawnInfo;
	ACharacter* RatCharacter = GetWorld()->SpawnActor<ARatCharacter>(RatCharacterBP, TargetPoint->GetActorLocation(), TargetPoint->GetActorRotation(), SpawnInfo);
	
	ARatAIController* RatController = Cast<ARatAIController>(RatCharacter->GetController());
	DanglingRats.Add(RatController);
}

void ARatManager::DestroyRat(ARatAIController* DestroyedRat)
{
	
}

void ARatManager::TransmitOrder(const FRatsOrder Order)
{
	for (ARatAIController* Rat : ControlledRats)
	{
		Rat->RecieveOrder(Order);
	}
}

// Called every frame
void ARatManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	/*timer += DeltaTime;
	if (timer >= SpawnRate)
	{
		timer = 0;
		CreateRat(SpawnTarget);
	}*/

}

