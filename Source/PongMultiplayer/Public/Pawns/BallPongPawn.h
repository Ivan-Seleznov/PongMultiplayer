// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawns/BasePawn.h"
#include "BallPongPawn.generated.h"

/**
 * 
 */
UCLASS()
class PONGMULTIPLAYER_API ABallPongPawn : public ABasePawn
{
	GENERATED_BODY()

public:
	ABallPongPawn();
	
	virtual void Tick(float DeltaSeconds) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	const FVector& GetBallSpawnLocation() const {return BallSpawnLocation;}
	
protected:
	UPROPERTY(Replicated,VisibleAnywhere,BlueprintReadOnly)
	FVector BallVelocity;

	UPROPERTY(Replicated,EditDefaultsOnly,BlueprintReadOnly)
	float BallSpeed = 500.f;

	
	UPROPERTY() FVector BallSpawnLocation;
	
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnBallHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
