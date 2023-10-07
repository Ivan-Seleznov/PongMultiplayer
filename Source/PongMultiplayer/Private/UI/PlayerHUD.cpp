// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerHUD.h"
#include "Blueprint/UserWidget.h"
#include "GameModes/PongGameState.h"
#include "Kismet/GameplayStatics.h"

void APlayerHUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	APongGameState* PongGameState = Cast<APongGameState>(UGameplayStatics::GetGameState(this));
	if (!PongGameState || !WaitingScreenWidget) return;

	if (PongGameState->IsAllPlayersConnected())
	{
		if (WaitingScreenWidget->IsVisible())
		{
			WaitingScreenWidget->SetVisibility(ESlateVisibility::Collapsed);
		}
		if (!PlayerHUDWidget->IsVisible())
		{
			PlayerHUDWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}

}

void APlayerHUD::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* OwningPlayerController = GetOwningPlayerController();
	if (!OwningPlayerController) return;
	
	WaitingScreenWidget = CreateWidget(OwningPlayerController,WaitingScreenWidgetClass);
	WaitingScreenWidget->AddToViewport();
	WaitingScreenWidget->SetVisibility(ESlateVisibility::Visible);
	
	PlayerHUDWidget = CreateWidget(OwningPlayerController,PlayerHUDWidgetClass);
	PlayerHUDWidget->AddToViewport();
	PlayerHUDWidget->SetVisibility(ESlateVisibility::Collapsed);
}
