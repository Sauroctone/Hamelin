// Fill out your copyright notice in the Description page of Project Settings.

#include "FluteManager.h"
#include "CustomGameInstance.h"


// Sets default values
AFluteManager::AFluteManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFluteManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFluteManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

