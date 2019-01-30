// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomGameInstance.h"
#include "EngineUtils.h"

void UCustomGameInstance::OnStart()
{
	Super::OnStart();
	UWorld* World = GetWorld();
	if (World)
	{
		for (TActorIterator<AFluteManager> Itr(World); Itr; ++Itr) 
		{
			FluteMan = *Itr;
		}

		for (TActorIterator<ARatManager> Itr(World); Itr; ++Itr)
		{	
			RatMan = *Itr;
		}
	}
}
