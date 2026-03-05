// Copyright Epic Games, Inc. All Rights Reserved.

#include "BWObserverPawn.h"

#include "Camera/CameraComponent.h"
#include "Camera/PlayerCameraManager.h"
#include "Components/InputComponent.h"
#include "Components/SceneComponent.h"
#include "Engine/Scene.h"
#include "GameFramework/PlayerController.h"

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
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Keep panorama brightness comfortable without editing level assets.
	CameraComponent->PostProcessBlendWeight = 1.0f;
	CameraComponent->PostProcessSettings.bOverride_AutoExposureMethod = true;
	CameraComponent->PostProcessSettings.AutoExposureMethod = EAutoExposureMethod::AEM_Manual;
	CameraComponent->PostProcessSettings.bOverride_AutoExposureApplyPhysicalCameraExposure = true;
	CameraComponent->PostProcessSettings.AutoExposureApplyPhysicalCameraExposure = false;
	CameraComponent->PostProcessSettings.bOverride_AutoExposureBias = true;
	CameraComponent->PostProcessSettings.AutoExposureBias = -1.0f;
}

void ABWObserverPawn::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController == nullptr && GetWorld() != nullptr)
	{
		PlayerController = GetWorld()->GetFirstPlayerController();
	}

	if (bLimitPitch && PlayerController != nullptr && PlayerController->PlayerCameraManager != nullptr)
	{
		// Hide nadir/tripod area in panoramas for desktop mouse-look.
		PlayerController->PlayerCameraManager->ViewPitchMin = ViewPitchMinLimit;
		PlayerController->PlayerCameraManager->ViewPitchMax = ViewPitchMaxLimit;
	}
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
