// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/PongGameState.h"

#include "Net/UnrealNetwork.h"

void APongGameState::OnAllPlayersConnected()
{
	bAllPlayersConnected = true;
}

void APongGameState::IncrementScore(int PlayerNumber)
{
	if (PlayerNumber == 1)
	{
		PlayerOneScore++;
	}
	else if (PlayerNumber == 2)
	{
		PlayerTwoScore++;
	}
}

void APongGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ThisClass,PlayerOneScore);
	DOREPLIFETIME(ThisClass,PlayerTwoScore);
	DOREPLIFETIME(ThisClass,bAllPlayersConnected);
}