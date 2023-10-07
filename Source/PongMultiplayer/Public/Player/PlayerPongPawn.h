// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawns/BasePawn.h"
#include "PlayerPongPawn.generated.h"

class UCameraComponent;
class USpringArmComponent;
/**
 * Player pawn class
 */
UCLASS()
class PONGMULTIPLAYER_API APlayerPongPawn : public ABasePawn
{
	GENERATED_BODY()
public:
	APlayerPongPawn();
	
	virtual UPawnMovementComponent* GetMovementComponent() const override;
	
protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Components")
	UPongMovementComponent* PongMovementComponent;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
