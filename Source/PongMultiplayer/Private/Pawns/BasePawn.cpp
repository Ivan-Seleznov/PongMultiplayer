// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/BasePawn.h"

#include "GameFramework/FloatingPawnMovement.h"

ABasePawn::ABasePawn()
{
	PawnMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PawnMesh"));
	PawnMovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>("FloatingPawnMovementComponent");
}
