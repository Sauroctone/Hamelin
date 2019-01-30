// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RatsOrder.generated.h"

#define FOLLOW_ORDER 0
#define ATTACK_ORDER 1
#define FAILED_ORDER 2

USTRUCT()
struct FRatsOrder
{
	GENERATED_BODY()

	FRatsOrder(int _type = FOLLOW_ORDER, AActor* _target = nullptr) : OrderType(_type), Target(_target) { }

	UPROPERTY()
	int32 OrderType;

	UPROPERTY()
	AActor* Target;
};
	
