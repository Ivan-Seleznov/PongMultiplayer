// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/PongPlayerController.h"
#include "EnhancedInputSubsystems.h"

void APongPlayerController::InitializePlayerInput(UInputComponent* PlayerInputComponent)
{
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (!EnhancedInputComponent) return;

	
	const APawn* PlayerPawn = GetPawn();
	if (!PlayerPawn) return;

	const ULocalPlayer* LocalPlayer = GetLocalPlayer();
	if (!LocalPlayer) return;
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if (!Subsystem) return;

	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(DefaultMappingContext,0);

	EnhancedInputComponent->BindAction(MoveInputAction,ETriggerEvent::Triggered,this,&ThisClass::Input_Move);
}

void APongPlayerController::Input_Move(const FInputActionValue& Value)
{
	APawn* PlayerPawn = GetPawn();
	if (!PlayerPawn) return;
	
	const FVector2D MovementVector = Value.Get<FVector2D>();
	if (MovementVector.X != 0)
	{
		PlayerPawn->AddMovementInput(PlayerPawn->GetActorRightVector(), MovementVector.X);
	}
}