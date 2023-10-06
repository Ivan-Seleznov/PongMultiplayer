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
	FPawnSavedMove(FVector PawnClientLoc,FVector Direction,float Delta,float Value);
	
	UPROPERTY() FVector WorldDirection;
	UPROPERTY() float DeltaTime;
	UPROPERTY() float ScaleValue;
	UPROPERTY() FVector PawnDeltaLoc;
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
	// Sets default values for this component's properties
	UPongMovementComponent();

	virtual void InitializeComponent() override;

	//Call on client
	void MovePawn(const FVector& WorldDirection,float ScaleValue);

	UFUNCTION(Unreliable,Server)
	void Server_MovePawn(const FPawnSavedMove& PawnSavedMove);

	UFUNCTION(Unreliable,Client)
	void Client_CorrectPawnMove(const FVector& NewPawnLoc);
	
	virtual void SetSpeed(float NewSpeed);
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Replicated)
	float PawnSpeed = 1300.f;
	
	UPROPERTY(Transient,BlueprintReadOnly)
	ABasePawn* BasePawnOwner;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

};
