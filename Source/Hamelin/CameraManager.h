// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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
	float ZoomOutScreenDivisor;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ZoomInScreenDivisor;
	UPROPERTY(EditAnywhere)
	float ZoomOutSpeedZ;
	UPROPERTY(EditAnywhere)
	float ZoomOutSpeedX;
	UPROPERTY(EditAnywhere)
	float ZoomInSpeedZ;
	UPROPERTY(EditAnywhere)
	float ZoomInSpeedX;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	APlayerController * PlayerController;
	FVector TargetLocation;
	FVector PlayerLocation;
	FVector FirstLocation;
	FVector SecondLocation;
	FVector AverageLocation;
	FVector2D PlayerScreenLoc;
	FVector2D FirstScreenLoc;
	FVector2D SecondScreenLoc;
	int targetCount;
	int screenWidth;
	int screenHeight;
	bool mustZoomOut;
	bool mustZoomIn;
	FVector ZoomOffset;
	FVector FinalOffset;

	void SetAverageTargetLocation();
	void CheckScreenLocation(FVector _worldLoc, FVector2D &_screenLoc);
	bool IsTowardsEdgeOfScreen(FVector2D _screenLoc);
	bool IsTowardsCenterOfScreen(FVector2D _screenLoc);
	void ZoomOut(float DeltaTime);
	void ZoomIn(float DeltaTime);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
