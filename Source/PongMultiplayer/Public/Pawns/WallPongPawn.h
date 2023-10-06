// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawns/BasePawn.h"
#include "WallPongPawn.generated.h"

class UCameraComponent;
class USpringArmComponent;
/**
 * 
 */
UCLASS()
class PONGMULTIPLAYER_API AWallPongPawn : public ABasePawn
{
	GENERATED_BODY()
public:
	AWallPongPawn();
	
protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Components")
	UCameraComponent* CameraComponent;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
