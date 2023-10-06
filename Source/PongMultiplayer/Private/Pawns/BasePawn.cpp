// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/BasePawn.h"
#include "Pawns/Components/PongMovementComponent.h"

ABasePawn::ABasePawn()
{
	PawnMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PawnMesh"));
	PongMovementComponent = CreateDefaultSubobject<UPongMovementComponent>("PongMovementComponent");

	PongMovementComponent->SetIsReplicated(true);
}

