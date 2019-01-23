// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"
#include "EngineMinimal.h"
#include "Engine/Public/DrawDebugHelpers.h"

// Sets default values
ACameraManager::ACameraManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	targetCount = 3;
}

// Called when the game starts or when spawned
void ACameraManager::BeginPlay()
{
	Super::BeginPlay();

	FollowCamera->SetActorLocation(PlayerTarget->GetActorLocation() + BaseCameraOffset);
	
	if (!FirstCameraTarget)
		targetCount--;

	if (!SecondCameraTarget)
		targetCount--;

	PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerController->GetViewportSize(screenWidth, screenHeight);
}

void ACameraManager::SetAverageTargetLocation()
{
	PlayerLocation = PlayerTarget->GetActorLocation();
	FirstLocation = FirstCameraTarget ? FirstCameraTarget->GetActorLocation() : FVector::ZeroVector;
	SecondLocation = SecondCameraTarget ? SecondCameraTarget->GetActorLocation() : FVector::ZeroVector;
	AverageLocation = (PlayerTarget->GetActorLocation() + FirstLocation + SecondLocation) / targetCount;
}

void ACameraManager::CheckScreenLocation(FVector _worldLoc, FVector2D &_screenLoc)
{
	PlayerController->ProjectWorldLocationToScreen(_worldLoc, _screenLoc);
	mustZoomOut = IsTowardsEdgeOfScreen(_screenLoc);
	mustZoomIn = mustZoomOut ? false : IsTowardsCenterOfScreen(_screenLoc);
}

bool ACameraManager::IsTowardsEdgeOfScreen(FVector2D _screenLoc)
{
	if (_screenLoc.X < screenWidth / ZoomOutScreenDivisor || _screenLoc.X > screenWidth - screenWidth / ZoomOutScreenDivisor || _screenLoc.Y < screenHeight / ZoomOutScreenDivisor || _screenLoc.Y > screenHeight - screenHeight / ZoomOutScreenDivisor)
	{
		return true;
	}
	return false;
}

bool ACameraManager::IsTowardsCenterOfScreen(FVector2D _screenLoc)
{
	if (_screenLoc.X > 0 - screenWidth / ZoomInScreenDivisor || _screenLoc.X < 0 + screenWidth / ZoomInScreenDivisor || _screenLoc.Y > 0 + screenHeight / ZoomInScreenDivisor || _screenLoc.Y < 0 + screenHeight / ZoomInScreenDivisor)
	{
		return true;
	}
	return false;
}

void ACameraManager::ZoomOut(float DeltaTime)
{
	ZoomOffset.Z += ZoomOutSpeedZ * DeltaTime;
	ZoomOffset.X -= ZoomOutSpeedX * DeltaTime;
}

void ACameraManager::ZoomIn(float DeltaTime)
{
	ZoomOffset.Z -= ZoomInSpeedZ * DeltaTime;
	ZoomOffset.X += ZoomInSpeedX * DeltaTime;
}

// Called every frame
void ACameraManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	SetAverageTargetLocation();

	CheckScreenLocation(PlayerLocation, PlayerScreenLoc);
	if (FirstCameraTarget)
		CheckScreenLocation(FirstLocation, FirstScreenLoc);
	if (SecondCameraTarget)
		CheckScreenLocation(SecondLocation, SecondScreenLoc);

	if (mustZoomOut)
		ZoomOut(DeltaTime);
	else if (mustZoomIn)
		ZoomIn(DeltaTime);

	GEngine->AddOnScreenDebugMessage(-1, 0.3f, FColor::Yellow, mustZoomOut ? "True" : "False");

	FinalOffset = BaseCameraOffset + ZoomOffset;
	FinalOffset.X = FMath::Clamp(FinalOffset.X, MaxCameraOffset.X, MinCameraOffset.X);
	FinalOffset.Z = FMath::Clamp(FinalOffset.Z, MinCameraOffset.Z, MaxCameraOffset.Z);

	TargetLocation = AverageLocation + FinalOffset;
	FollowCamera->SetActorLocation(FMath::Lerp(FollowCamera->GetActorLocation(), TargetLocation, CameraLerp * DeltaTime));	
}