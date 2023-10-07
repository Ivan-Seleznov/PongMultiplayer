// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "GoalTrigger.generated.h"

/**
 * 
 */
UCLASS()
class PONGMULTIPLAYER_API AGoalTrigger : public ATriggerBox
{
	GENERATED_BODY()
public:
	AGoalTrigger();
	
	UFUNCTION()
	void OnBeginOverlap(AActor* OverlappedActor,AActor* OtherActor);
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	int PlayerNumber;
};
