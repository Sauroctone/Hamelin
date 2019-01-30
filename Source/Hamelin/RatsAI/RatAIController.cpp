// Fill out your copyright notice in the Description page of Project Settings.

#include "RatsAI/RatState.h"
#include "RatAIController.h"

ARatAIController::ARatAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{
}

void ARatAIController::RecieveOrder(FRatsOrder order)
{

}
