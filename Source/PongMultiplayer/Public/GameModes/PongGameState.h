// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "PongGameState.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAllPlayersConnected);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerScoreChanged,int,NewPlayerScore);

/**
 * Pong GameState class. Contains players score
 */
UCLASS()
class PONGMULTIPLAYER_API APongGameState : public AGameState
{
	GENERATED_BODY()

public:
	FAllPlayersConnected OnAllPlayersConnectedDelegate;

	FPlayerScoreChanged OnPlayerOneScoreChanged;
	FPlayerScoreChanged OnPlayerTwoScoreChanged;

    void OnAllPlayersConnected();

	void IncrementScore(int PlayerNumber);
	
protected:
	UFUNCTION(Reliable,Client)
	void Client_OnAllPlayersConnected();

	UFUNCTION()
	void OnRep_PlayerOneScore();

	UFUNCTION()
	void OnRep_PlayerTwoScore();
	
	UPROPERTY(Replicated, ReplicatedUsing = OnRep_PlayerOneScore, EditAnywhere, BlueprintReadWrite, Category = "Score")
	int PlayerOneScore;

	UPROPERTY(Replicated,ReplicatedUsing = OnRep_PlayerTwoScore, EditAnywhere, BlueprintReadWrite, Category = "Score")
	int PlayerTwoScore;

	
};
