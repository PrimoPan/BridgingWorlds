// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BWObserverPawn.generated.h"

class UCameraComponent;
class USceneComponent;

DECLARE_MULTICAST_DELEGATE(FBWConfirmEvent);

UCLASS()
class BRIDGINGWORLDS_API ABWObserverPawn : public APawn
{
	GENERATED_BODY()

public:
	ABWObserverPawn();

	FBWConfirmEvent OnConfirm;

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = "View")
	bool bLimitPitch = true;

	UPROPERTY(EditAnywhere, Category = "View", meta = (ClampMin = "-89.0", ClampMax = "89.0"))
	float ViewPitchMinLimit = -60.0f;

	UPROPERTY(EditAnywhere, Category = "View", meta = (ClampMin = "-89.0", ClampMax = "89.0"))
	float ViewPitchMaxLimit = 89.0f;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UCameraComponent> CameraComponent;

	void Turn(float Value);
	void LookUp(float Value);
	void HandleConfirmPressed();
};
