// Fill out your copyright notice in the Description page of Project Settings.

#include "RatState_Moving.h"

void URatState_Moving::OnStateEnter(ARatAIController * PassedOwnerController)
{
	Super::OnStateEnter(PassedOwnerController);
	//Init movement towards target
}

void URatState_Moving::Update(float DeltaTime)
{
	//Check if arrived, if arrived, switch to correct state
}

void URatState_Moving::OnStateExit()
{
	//Stop movement if in motion
}
