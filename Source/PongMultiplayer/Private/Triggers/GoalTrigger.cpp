// Fill out your copyright notice in the Description page of Project Settings.


#include "Triggers/GoalTrigger.h"

#include "Pawns/BallPongPawn.h"

AGoalTrigger::AGoalTrigger()
{
	OnActorBeginOverlap.AddDynamic(this,&ThisClass::OnBeginOverlap);
}

void AGoalTrigger::OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (ABallPongPawn* BallPawn = Cast<ABallPongPawn>(OtherActor))
	{
		BallPawn->SetActorLocation(BallPawn->GetBallSpawnLocation());
	}
}
