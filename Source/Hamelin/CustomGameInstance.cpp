// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomGameInstance.h"
#include "EngineUtils.h"

void UCustomGameInstance::OnStart()
{
	if (GetWorld())
	{
		for (TActorIterator<AFluteManager> Itr(GetWorld()); Itr; ++Itr) 
		{
			FluteMan = *Itr;
		}
	}
}
