// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RatsAI/RatState.h"
#include "RatState_Dying.generated.h"


/**
 * 
 */
UCLASS()
class HAMELIN_API URatState_Dying : public URatState
{
	GENERATED_BODY()

	public:
		virtual URatState* RecieveOrder(FRatsOrder Order) override;
		virtual void OnStateEnter(ARatAIController * PassedOwnerController) override;
		virtual void Update(float DeltaTime) override;
		virtual void OnStateExit() override;

	private :
		float DeathTimer = 2.0f; //Find a way to setup with Rat properties
		bool bIsDead = false;
	
};
