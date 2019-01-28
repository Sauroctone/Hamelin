// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "HamelinCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "CustomGameInstance.h"

//////////////////////////////////////////////////////////////////////////
// AHamelinCharacter

AHamelinCharacter::AHamelinCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AHamelinCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AHamelinCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AHamelinCharacter::MoveRight);
	PlayerInputComponent->BindAction("Focus", IE_Pressed, this, &AHamelinCharacter::Focus);
	PlayerInputComponent->BindAction("Focus", IE_Released, this, &AHamelinCharacter::StopFocus);

	PlayerInputComponent->BindAction("FirstTarget", IE_Pressed, this, &AHamelinCharacter::FirstTarget);
	PlayerInputComponent->BindAction("SecondTarget", IE_Pressed, this, &AHamelinCharacter::SecondTarget);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AHamelinCharacter::Attack);
	PlayerInputComponent->BindAction("Follow", IE_Pressed, this, &AHamelinCharacter::Follow);
}

void AHamelinCharacter::BeginPlay()
{
	Super::BeginPlay();

	UCustomGameInstance* SGI = nullptr;
	if (GetWorld())
		SGI = Cast<UCustomGameInstance>(GetWorld()->GetGameInstance());
	if (SGI)
	{
		FluteMan = SGI->FluteMan;
	}
}

void AHamelinCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
		UPawnMovementComponent* MovementComponent = GetMovementComponent();
		
		if (MovementComponent)
		{
			UE_LOG(LogTemp, Warning, TEXT("Has component"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No component"));
		}


		UE_LOG(LogTemp, Warning, TEXT("Value is %f"), Value);
		UE_LOG(LogTemp, Warning, TEXT("Direction is %s"), *Direction.ToString());
	}
}

void AHamelinCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
		//UE_LOG(LogTemp, Warning, TEXT("Result is %s"), *Direction.ToString())
	}
}

void AHamelinCharacter::Focus()
{
	FluteMan->OnFocused.Broadcast(true);
}

void AHamelinCharacter::StopFocus()
{
	FluteMan->OnFocused.Broadcast(false);
}

void AHamelinCharacter::FirstTarget()
{
}

void AHamelinCharacter::SecondTarget()
{
}

void AHamelinCharacter::Attack()
{
}

void AHamelinCharacter::Follow()
{
}
