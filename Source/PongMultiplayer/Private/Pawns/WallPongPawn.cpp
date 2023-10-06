// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/WallPongPawn.h"

#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"

AWallPongPawn::AWallPongPawn()
{
	ShapeComponent = CreateDefaultSubobject<UBoxComponent>("Box Collision");
	RootComponent = ShapeComponent;

	PawnMesh->SetupAttachment(RootComponent);
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArmComponent->SetupAttachment(RootComponent);
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera Component");
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void AWallPongPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
