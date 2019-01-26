// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RatsAI/RatAIController.h"
#include "RatManager.generated.h"




UCLASS()
class HAMELIN_API ARatManager : public AActor
{
	GENERATED_BODY()
	
	public:	
		ARatManager();
		virtual void Tick(float DeltaTime) override;

		//RAT MANAGEMENT
		void CreateRat(AActor* TargetPoint); //Spawns a character and an ai controller to possess it
		void DestroyRat(ARatAIController* DestroyedRat); //Free the memory

		//Debug
		void Debug();

		UPROPERTY(EditAnywhere)
			AActor* SpawnTarget;

	protected:
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;
		TArray<ARatAIController*> ControlledRats;
		TArray<ARatAIController*> DanglingRats;

};
