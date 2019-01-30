// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FluteManager.h"
#include "CameraManager.generated.h"

UCLASS()
class HAMELIN_API ACameraManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraManager();

	UPROPERTY(EditAnywhere)
	class ACameraActor* FollowCamera;
	UPROPERTY(EditAnywhere)
	class AActor* PlayerTarget;
	UPROPERTY(EditAnywhere)
	class AActor* FirstCameraTarget;
	UPROPERTY(EditAnywhere)
	class AActor* SecondCameraTarget;

	UPROPERTY(EditAnywhere)
	FVector BaseCameraOffset;
	UPROPERTY(EditAnywhere)
	FVector MinCameraOffset;
	UPROPERTY(EditAnywhere)
	FVector MaxCameraOffset;
	UPROPERTY(EditAnywhere)
	float CameraLerp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float zoomOutDistanceFromBorder;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float zoomInDistanceFromCenter;
	UPROPERTY(EditAnywhere)
	float ZoomOutSpeedZ;
	UPROPERTY(EditAnywhere)
	float ZoomOutSpeedX;
	UPROPERTY(EditAnywhere)
	float ZoomInSpeedZ;
	UPROPERTY(EditAnywhere)
	float ZoomInSpeedX;
	
	UPROPERTY(BlueprintReadOnly)
	FVector2D PlayerScreenLoc;
	UPROPERTY(BlueprintReadOnly)
	FVector2D FirstScreenLoc;
	UPROPERTY(BlueprintReadOnly)
	FVector2D SecondScreenLoc;
	
	UPROPERTY(BlueprintReadOnly)
	int screenWidth;
	UPROPERTY(BlueprintReadOnly)
	int screenHeight;

	UFUNCTION()
	void OnFocused(bool _isFocused);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	APlayerController* PlayerController;
	AFluteManager* FluteMan;
	FVector TargetLocation;
	FVector PlayerLocation;
	FVector FirstLocation;
	FVector SecondLocation;
	FVector AverageLocation;
	int targetCount;
	bool mustZoomOut;
	FVector ZoomOffset;
	FVector FinalOffset;
	int targetsAtCenter;
	bool isFocused;

	void SetAverageTargetLocation();
	void CheckScreenLocation(FVector _worldLoc, FVector2D &_screenLoc);
	bool IsTowardsEdgeOfScreen(float viewLocX, float viewLocY);
	int IsTowardsCenterOfScreen(float viewLocX, float viewLocY);
	void ZoomOut(float DeltaTime);
	void ZoomIn(float DeltaTime);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};