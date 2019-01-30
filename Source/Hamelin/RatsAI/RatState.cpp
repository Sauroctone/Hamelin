// Fill out your copyright notice in the Description page of Project Settings.

#include "RatState.h"

URatState::URatState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{}

URatState* URatState::RecieveOrder(FRatsOrder Order)
{
	return nullptr;
}

void URatState::OnStateEnter()
{
}

void URatState::Update()
{
}

void URatState::OnStateExit()
{
}
