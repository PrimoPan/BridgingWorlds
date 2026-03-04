// Copyright Epic Games, Inc. All Rights Reserved.

#include "BWObserverPawn.h"

#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/SceneComponent.h"

ABWObserverPawn::ABWObserverPawn()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(SceneRoot);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SceneRoot);
	CameraComponent->bUsePawnControlRotation = true;

	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;
}

void ABWObserverPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ABWObserverPawn::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ABWObserverPawn::LookUp);
	PlayerInputComponent->BindAction(TEXT("Confirm"), IE_Pressed, this, &ABWObserverPawn::HandleConfirmPressed);
}

void ABWObserverPawn::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void ABWObserverPawn::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void ABWObserverPawn::HandleConfirmPressed()
{
	UE_LOG(LogTemp, Log, TEXT("[BW] Confirm"));
	OnConfirm.Broadcast();
}
