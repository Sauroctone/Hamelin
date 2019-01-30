// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
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
		virtual void Update();
		virtual void OnStateEnter();
		virtual void OnStateExit();
	
	
};
