// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "PongGameMode.generated.h"

class ABallPongPawn;
class APlayerPongPawn;
class APlayerStart;
class ABaseCharacter;
/**
 * Pong GameMode class
 */
UCLASS()
class PONGMULTIPLAYER_API APongGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	const FVector& GetBallSpawnLocation() const {return BallSpawnLocation;}

	void OnBallInGoal(int PlayerNumber);
	
	void PostLogin(APlayerController* NewPlayer) override;
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Game")
	FName BallSpawnPointTag;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Game")
	FVector BallSpawnLocation;

	TArray<const APlayerStart*> PlayerStarts;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Game")
	int MaxPlayersCount = 2;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Classes")
	TSubclassOf<APlayerPongPawn> PlayerPawnClass;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Classes")
	TSubclassOf<ABallPongPawn> BallPawnClass;
	
	TArray<APlayerController*> ConnectedControllers;

	void StartGame();
	void SpawnBall();
private:
	void SetPlayerStarts();
	FVector GetBallSpawnPointLocation() const;

	ABallPongPawn* BallPongPawn;
};
