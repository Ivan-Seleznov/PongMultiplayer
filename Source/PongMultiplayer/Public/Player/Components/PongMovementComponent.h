// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "PongMovementComponent.generated.h"

USTRUCT()
struct FPawnSavedMove
{
	GENERATED_BODY()

	FPawnSavedMove();
	FPawnSavedMove(FVector PawnLoc,FVector Acceleration,float Delta);

	UPROPERTY() FVector PawnLoc;
	UPROPERTY() FVector ControlAcceleration;
	UPROPERTY() float DeltaTime;
};

class ABasePawn;
/*
 * Custom Pong Pawn Movement Component with movement replication
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PONGMULTIPLAYER_API UPongMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()

public:	
	UPongMovementComponent();

	virtual void InitializeComponent() override;

	//Call on client
	void MovePawn(const FVector& ControlAcceleration, float DeltaTime);

	UFUNCTION(Unreliable,Server)
	void Server_MovePawn(const FPawnSavedMove& PawnSavedMove);

	UFUNCTION(Unreliable,Client)
	void Client_CorrectPawnMove(const FVector& NewPawnLoc);
	
	virtual void SetSpeed(float NewSpeed);

protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Replicated)
	float PawnSpeed = 1300.f;
	
	UPROPERTY(Transient,BlueprintReadOnly)
	ABasePawn* BasePawnOwner;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

};
