// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "PongGameState.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerScoreChanged);

/**
 * Pong GameState class. Contains players score
 */
UCLASS()
class PONGMULTIPLAYER_API APongGameState : public AGameState
{
	GENERATED_BODY()

public:
    void OnAllPlayersConnected();

	void IncrementScore(int PlayerNumber);

	bool IsAllPlayersConnected() const {return bAllPlayersConnected;}
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	int GetPlayerOneScore() const {return PlayerOneScore;}
	int GetPlayerTwoScore() const {return PlayerTwoScore;}

protected:
	
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Score")
	int PlayerOneScore;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Score")
	int PlayerTwoScore;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Score")
	bool bAllPlayersConnected;
};
