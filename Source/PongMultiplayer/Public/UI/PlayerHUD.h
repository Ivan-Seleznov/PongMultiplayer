// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerHUD.generated.h"

/**
 * Player HUD class
 */
UCLASS()
class PONGMULTIPLAYER_API APlayerHUD : public AHUD
{
	GENERATED_BODY()
public:
	virtual void Tick(float DeltaSeconds) override;
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> WaitingScreenWidgetClass;

private:
	UPROPERTY() UUserWidget* PlayerHUDWidget;
	UPROPERTY() UUserWidget* WaitingScreenWidget;
};
