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
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UCameraComponent> CameraComponent;

	void Turn(float Value);
	void LookUp(float Value);
	void HandleConfirmPressed();
};
