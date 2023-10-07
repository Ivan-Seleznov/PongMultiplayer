// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/PongGameState.h"

void APongGameState::OnAllPlayersConnected()
{
	Client_OnAllPlayersConnected();
}

void APongGameState::IncrementScore(int PlayerNumber)
{
	if (!HasAuthority()) return;
	
	if (PlayerNumber == 1)
	{
		PlayerOneScore++;
	}
	else if (PlayerNumber == 2)
	{
		PlayerTwoScore++;
	}
}

void APongGameState::OnRep_PlayerOneScore()
{
	OnPlayerOneScoreChanged.Broadcast(PlayerOneScore);
}

void APongGameState::OnRep_PlayerTwoScore()
{
	OnPlayerOneScoreChanged.Broadcast(PlayerTwoScore);
}

void APongGameState::Client_OnAllPlayersConnected_Implementation()
{
	OnAllPlayersConnectedDelegate.Broadcast();
}
