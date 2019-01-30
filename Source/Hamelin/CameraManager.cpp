// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"
#include "EngineMinimal.h"
#include "Engine/Public/DrawDebugHelpers.h"
#include "Engine.h"
#include "CustomGameInstance.h"

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

	UCustomGameInstance* SGI = nullptr;
	if (GetWorld())
		SGI = Cast<UCustomGameInstance>(GetWorld()->GetGameInstance());
	if (SGI)
	{
		FluteMan = SGI->FluteMan;
		FluteMan->OnFocused.AddDynamic(this, &ACameraManager::OnFocused);
	}	
}

void ACameraManager::SetAverageTargetLocation()
{
	PlayerLocation = PlayerTarget->GetActorLocation();
	FirstLocation = FirstCameraTarget ? FirstCameraTarget->GetActorLocation() : FVector::ZeroVector;
	SecondLocation = SecondCameraTarget ? SecondCameraTarget->GetActorLocation() : FVector::ZeroVector;
	AverageLocation = (PlayerLocation + FirstLocation + SecondLocation) / targetCount;
}

void ACameraManager::CheckScreenLocation(FVector _worldLoc, FVector2D &_screenLoc, float &viewLocX, float &viewLocY)
{
	PlayerController->ProjectWorldLocationToScreen(_worldLoc, _screenLoc);
	viewLocX = _screenLoc.X / screenWidth;
	viewLocY = _screenLoc.Y / screenHeight;

	UE_LOG(LogTemp, Warning, TEXT("%f, %f"), viewLocX, viewLocY);
	
	if (!mustZoomOut)
	{
		mustZoomOut = IsTowardsEdgeOfScreen(viewLocX, viewLocY);
	}
	
	targetsAtCenter += IsTowardsCenterOfScreen(viewLocX, viewLocY);
}

bool ACameraManager::IsTowardsEdgeOfScreen(float viewLocX, float viewLocY)
{
	if (viewLocX < 0 + zoomOutDistanceFromBorder || viewLocX > 1 - zoomOutDistanceFromBorder || viewLocY < 0 + zoomOutDistanceFromBorder || viewLocY > 1 - zoomOutDistanceFromBorder)
	{
		return true;
	}
	return false;
}

int ACameraManager::IsTowardsCenterOfScreen(float viewLocX, float viewLocY)
{
	if (viewLocX > 0.5f - zoomInDistanceFromCenter && viewLocX < 0.5f + zoomInDistanceFromCenter && viewLocY > 0.5f - zoomInDistanceFromCenter && viewLocY < 0.5f + zoomInDistanceFromCenter)
	{
		return 1;
	}
	return 0;
}

bool ACameraManager::IsOutOfCamera(float viewLocX, float viewLocY)
{
	if (viewLocX < 0 || viewLocX > 1 || viewLocY < 0 || viewLocY > 1)
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

void ACameraManager::ForgetTargetsOutOfFrame()
{
	if (FinalOffset.X == MaxCameraOffset.X)
	{
		if (IsOutOfCamera(playerViewX, playerViewY))
		{
			if (FirstCameraTarget)
			{
				if (SecondCameraTarget && FVector::Dist(FirstLocation, PlayerLocation) < FVector::Dist(SecondLocation, PlayerLocation))
				{
					SecondCameraTarget = nullptr;
				}
				else
				{
					FirstCameraTarget = nullptr;
				}

				targetCount--;
			}
		}

		if (FirstCameraTarget && IsOutOfCamera(firstViewX, firstViewY))
		{
			FirstCameraTarget = nullptr;
			targetCount--;
		}
		if (SecondCameraTarget && IsOutOfCamera(secondViewX, secondViewY))
		{
			SecondCameraTarget = nullptr;
			targetCount--;
		}
	}
}

void ACameraManager::OnFocused(bool _isFocused)
{
	isFocused = _isFocused;
	UKismetSystemLibrary::PrintString(GetWorld(), isFocused ? "FOCUSED" : "NOT FOCUSED", false, true, FColor::Yellow, .1f);
}

// Called every frame
void ACameraManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (!isFocused)
	{
		PlayerController->GetViewportSize(screenWidth, screenHeight);

		SetAverageTargetLocation();

		targetsAtCenter = 0;
		mustZoomOut = false;
		CheckScreenLocation(PlayerLocation, PlayerScreenLoc, playerViewX, playerViewY);
		if (FirstCameraTarget)
			CheckScreenLocation(FirstLocation, FirstScreenLoc, firstViewX, firstViewY);
		if (SecondCameraTarget)
			CheckScreenLocation(SecondLocation, SecondScreenLoc, secondViewX, secondViewY);

		UE_LOG(LogTemp, Warning, TEXT("targets at center : %d"), targetsAtCenter);
		UE_LOG(LogTemp, Warning, TEXT("target count : %d"), targetCount);
		//UKismetSystemLibrary::PrintString(GetWorld(), mustZoomOut ? "Zoom out" : "No zoom", false, true);

		if (mustZoomOut)
			ZoomOut(DeltaTime);
		else if (targetsAtCenter == targetCount)
			ZoomIn(DeltaTime);

		FinalOffset = BaseCameraOffset + ZoomOffset;

		if (FinalOffset.X < MaxCameraOffset.X)
			FinalOffset.X = MaxCameraOffset.X;
		else if (FinalOffset.X > MinCameraOffset.X)
			FinalOffset.X = MinCameraOffset.X;

		if (FinalOffset.Z > MaxCameraOffset.Z)
			FinalOffset.Z = MaxCameraOffset.Z;
		else if (FinalOffset.Z < MinCameraOffset.Z)
			FinalOffset.Z = MinCameraOffset.Z;

		TargetLocation = AverageLocation + FinalOffset;
		FollowCamera->SetActorLocation(FMath::Lerp(FollowCamera->GetActorLocation(), TargetLocation, CameraLerp * DeltaTime));

		ForgetTargetsOutOfFrame();
	}
}