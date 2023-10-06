// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

class UFloatingPawnMovement;

UCLASS(Abstract)
class PONGMULTIPLAYER_API ABasePawn : public APawn
{
	GENERATED_BODY()
	
public:
	ABasePawn();
	
protected:
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Components")
	UShapeComponent* ShapeComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* PawnMesh;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components")
	UFloatingPawnMovement* PawnMovementComponent;
};
