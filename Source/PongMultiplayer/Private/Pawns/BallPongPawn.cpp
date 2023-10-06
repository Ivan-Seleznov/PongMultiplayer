// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/BallPongPawn.h"

#include "Components/CapsuleComponent.h"

ABallPongPawn::ABallPongPawn()
{
	ShapeComponent = CreateDefaultSubobject<UCapsuleComponent>("Capsule Collision");
	ShapeComponent->SetupAttachment(RootComponent);

	PawnMesh->SetupAttachment(RootComponent);
}
