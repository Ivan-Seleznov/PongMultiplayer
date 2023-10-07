// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ScoreWidget.h"

#include "Components/TextBlock.h"
#include "GameModes/PongGameState.h"
#include "Kismet/GameplayStatics.h"


void UScoreWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	APongGameState* PongGameState = Cast<APongGameState>(UGameplayStatics::GetGameState(this));
	if (!PongGameState) return;

	PlayerOneScoreTextBlock->SetText(FText::AsNumber(PongGameState->GetPlayerOneScore()));
	PlayerTwoScoreTextBlock->SetText(FText::AsNumber(PongGameState->GetPlayerTwoScore()));
}
