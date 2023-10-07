// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerPongPawn.h"

#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/PongPlayerController.h"
#include "Player/Components/PongMovementComponent.h"

APlayerPongPawn::APlayerPongPawn()
{
	ShapeComponent = CreateDefaultSubobject<UBoxComponent>("Box Collision");
	RootComponent = ShapeComponent;

	PawnMesh->SetupAttachment(RootComponent);
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArmComponent->SetupAttachment(RootComponent);
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera Component");
	CameraComponent->SetupAttachment(SpringArmComponent);

	PongMovementComponent = CreateDefaultSubobject<UPongMovementComponent>("Pong Movement Component");
}

UPawnMovementComponent* APlayerPongPawn::GetMovementComponent() const
{
	return PongMovementComponent;
}

void APlayerPongPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	APongPlayerController* PongPlayerController = Cast<APongPlayerController>(GetController());
	if (!PongPlayerController) return;

	PongPlayerController->InitializePlayerInput(PlayerInputComponent);
}
