// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/PongGameMode.h"

#include "Engine/TargetPoint.h"
#include "GameFramework/PlayerStart.h"
#include "GameModes/PongGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PlayerPongPawn.h"

void APongGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	
	if (GetNumPlayers() > MaxPlayersCount) return;
	
	ConnectedControllers.Add(NewPlayer);

	if (ConnectedControllers.Num() == MaxPlayersCount)
	{
		StartGame();
	}
}

void APongGameMode::BeginPlay()
{
	Super::BeginPlay();

	BallSpawnLocation = GetBallSpawnPointLocation();
	SetPlayerStarts();
}

void APongGameMode::StartGame()
{
	if (PlayerStarts.Num() < ConnectedControllers.Num())
	{
		UE_LOG(LogTemp,Fatal,TEXT("Player start is less than max players count"))
	}


	for (int i = 0; i < ConnectedControllers.Num(); i++)
	{
		APlayerPongPawn* PongPaw = GetWorld()->SpawnActor<APlayerPongPawn>(PlayerPawnClass,PlayerStarts[i]->GetActorLocation(),PlayerStarts[i]->GetActorRotation());
		ConnectedControllers[i]->Possess(PongPaw);
	}

	APongGameState* PongGameState = GetGameState<APongGameState>();
	if (PongGameState)
	{
		PongGameState->OnAllPlayersConnected();
	}
}

void APongGameMode::SetPlayerStarts()
{
	TArray<AActor*> PStarts;
	UGameplayStatics::GetAllActorsOfClass(this,APlayerStart::StaticClass(),PStarts);


	for (const auto& PStart : PStarts)
	{
		if (const APlayerStart* PlayerStart = Cast<APlayerStart>(PStart))
		{
			PlayerStarts.Add(PlayerStart);
		}
	}
}

FVector APongGameMode::GetBallSpawnPointLocation() const
{
	TArray<AActor*> Points;
	UGameplayStatics::GetAllActorsOfClassWithTag(this,ATargetPoint::StaticClass(),BallSpawnPointTag,Points);

	for (const auto& Point : Points)
	{
		if (const ATargetPoint* SpawnPoint = Cast<ATargetPoint>(Point))
		{
			return SpawnPoint->GetActorLocation();
		}
	}

	UE_LOG(LogTemp,Fatal,TEXT("BallSpawnLocation not found"))
	return FVector::ZeroVector;
}
