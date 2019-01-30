// Fill out your copyright notice in the Description page of Project Settings.

#include "RatState_Acting.h"
#include "RatState_Confused.h"

URatState* URatState_Acting::RecieveOrder(FRatsOrder Order)
{
	//Checks if the rats are uncharmed
	if (Order.OrderType == FAILED_ORDER)
	{
		return Cast<URatState>(NewObject<URatState_Confused>());
	}
	else //Check for normal order
	{
		Super::RecieveOrder(Order);
	}

	return nullptr;
}

void URatState_Acting::OnStateEnter(ARatAIController * PassedOwnerController)
{
	Super::OnStateEnter(PassedOwnerController);
}

void URatState_Acting::Update(float DeltaTime)
{
}

void URatState_Acting::OnStateExit()
{
}
