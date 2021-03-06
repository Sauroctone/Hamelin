// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "FluteManager.h"
#include "CustomGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class HAMELIN_API UCustomGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	class AFluteManager * FluteMan;

protected:
	virtual void OnStart() override;
};
