// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "PongGameMode.generated.h"

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
	
	TArray<APlayerController*> ConnectedControllers;

	void StartGame();
private:
	void SetPlayerStarts();
	FVector GetBallSpawnPointLocation() const;
};
