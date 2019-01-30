// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Runtime/AIModule/Classes/Navigation/CrowdFollowingComponent.h"
#include "RatsAI/RatState.h"
#include "RatsOrder.h"
#include "RatAIController.generated.h"

/**
 * 
 */
UCLASS()
class HAMELIN_API ARatAIController : public AAIController
{
	GENERATED_BODY()

	public :
		ARatAIController(const FObjectInitializer& ObjectInitializer);
		void RecieveOrder(const FRatsOrder order);
	
	private :
		URatState* CurrentState;
		FRatsOrder CurrentOrder;
	
	
};
