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
	
	virtual URatState* RecieveOrder(FRatsOrder Order) override;
	
	
};
