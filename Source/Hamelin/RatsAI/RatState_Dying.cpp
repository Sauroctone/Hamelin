// Fill out your copyright notice in the Description page of Project Settings.

#include "RatState_Dying.h"
#include "RatsAI/RatAIController.h"
#include "CustomGameInstance.h"


URatState * URatState_Dying::RecieveOrder(FRatsOrder Order)
{
	return nullptr; //Can't recieve order when dying
}

void URatState_Dying::OnStateEnter(ARatAIController * PassedOwnerController)
{
	Super::OnStateEnter(PassedOwnerController);
	UE_LOG(LogTemp, Warning, TEXT("I'm dying !"));
}


void URatState_Dying::Update(float DeltaTime)
{
	if (DeathTimer > 0)
	{
		DeathTimer -= DeltaTime;
	}
	else if (!bIsDead)
	{
		bIsDead = true;
		OnStateExit();
	}
}

void URatState_Dying::OnStateExit()
{
	UE_LOG(LogTemp, Warning, TEXT("I'm DED"));
	UCustomGameInstance * CGI = Cast<UCustomGameInstance>(OwnersController->GetGameInstance());
	CGI->RatMan->DestroyRat(OwnersController);
}
