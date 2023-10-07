// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"
#include "PongPlayerController.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAllPlayersConnectedClient);

/**
 * 
 */
UCLASS()
class PONGMULTIPLAYER_API APongPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void InitializePlayerInput(UInputComponent* PlayerInputComponent);

	FAllPlayersConnectedClient AllPlayersConnectedClient;
protected:

	UFUNCTION()
	void OnAllPlayersConnected();

	UFUNCTION(Reliable,Client)
	void Client_OnAllPlayersConnected();

	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UInputAction* MoveInputAction;

	void Input_Move(const FInputActionValue& Value);
};
