// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreWidget.generated.h"

class UTextBlock;

/**
 * Score Widget class
 */
UCLASS()
class PONGMULTIPLAYER_API UScoreWidget : public UUserWidget
{
	GENERATED_BODY()
protected:

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerOneScoreTextBlock;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerTwoScoreTextBlock;
};
