// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FluteManager.generated.h"

UCLASS()
class HAMELIN_API AFluteManager : public AActor
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FToggleFocusMode, bool, isFocused);

public:	
	// Sets default values for this actor's properties
	AFluteManager();
	FToggleFocusMode OnFocused;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
