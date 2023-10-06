// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"
#include "PongPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PONGMULTIPLAYER_API APongPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	void InitializePlayerInput(UInputComponent* PlayerInputComponent);

protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UInputAction* MoveInputAction;

	void Input_Move(const FInputActionValue& Value);
};
