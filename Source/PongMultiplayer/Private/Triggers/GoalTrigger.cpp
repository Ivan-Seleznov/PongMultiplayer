// Fill out your copyright notice in the Description page of Project Settings.


#include "Triggers/GoalTrigger.h"

#include "GameModes/PongGameMode.h"
#include "GameModes/PongGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Pawns/BallPongPawn.h"

AGoalTrigger::AGoalTrigger()
{
	OnActorBeginOverlap.AddDynamic(this,&ThisClass::OnBeginOverlap);
}

void AGoalTrigger::OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (ABallPongPawn* BallPawn = Cast<ABallPongPawn>(OtherActor))
	{
		if (HasAuthority())
		{
			APongGameMode* PongGameMode = Cast<APongGameMode>(UGameplayStatics::GetGameMode(this));
			if (!PongGameMode) return;

			PongGameMode->OnBallInGoal(PlayerNumber);
		}
	}
}
