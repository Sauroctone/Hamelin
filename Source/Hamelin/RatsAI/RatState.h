// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RatsAI/RatAIController.h"
#include "RatsOrder.h"
#include "RatState.generated.h"


/**
 * 
 */
UCLASS()
class HAMELIN_API URatState : public UObject
{
	GENERATED_BODY()
	
	public:
		URatState(const FObjectInitializer& ObjectInitializer);
		virtual URatState* RecieveOrder(FRatsOrder Order);
		virtual void OnStateEnter(ARatAIController * PassedOwnerController);
		virtual void Update(float DeltaTime);
		virtual void OnStateExit();

	protected:
		ARatAIController* OwnersController = nullptr;
	
	
};
