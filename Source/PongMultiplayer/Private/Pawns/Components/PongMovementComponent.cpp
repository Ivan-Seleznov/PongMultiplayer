// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/Components/PongMovementComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Pawns/BasePawn.h"

float HM_MACRO_DURATION = 3.f;
#define SLOG(x,c) GEngine->AddOnScreenDebugMessage(-1,HM_MACRO_DURATION,c,x);

FPawnSavedMove::FPawnSavedMove()
{
}

FPawnSavedMove::FPawnSavedMove(FVector PawnLoc,FVector Direction,float Delta,float Value) : PawnDeltaLoc(PawnLoc), WorldDirection(Direction), DeltaTime(Delta),ScaleValue(Value)
{
}

UPongMovementComponent::UPongMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}

void UPongMovementComponent::InitializeComponent()
{
	Super::InitializeComponent();
	BasePawnOwner = Cast<ABasePawn>(GetPawnOwner());
}

void UPongMovementComponent::MovePawn(const FVector& WorldDirection,float ScaleValue)
{
	if (!PawnOwner) return;
	
	const float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	FVector DeltaLocation = WorldDirection * ScaleValue * DeltaTime * PawnSpeed;
	PawnOwner->AddActorLocalOffset(DeltaLocation,true);

	FPawnSavedMove PawnSavedMove(DeltaLocation,WorldDirection,DeltaTime,ScaleValue);
	
	Server_MovePawn(PawnSavedMove);
}

void UPongMovementComponent::Server_MovePawn_Implementation(const FPawnSavedMove& PawnSavedMove)
{
	FVector DeltaLocation = PawnSavedMove.WorldDirection * PawnSavedMove.ScaleValue * PawnSavedMove.DeltaTime * PawnSpeed;
	if (DeltaLocation == PawnSavedMove.PawnDeltaLoc)
	{
		PawnOwner->AddActorLocalOffset(DeltaLocation,true);
	}
	else
	{
		Client_CorrectPawnMove(GetActorLocation());
	}
}

void UPongMovementComponent::Client_CorrectPawnMove_Implementation(const FVector& NewPawnLoc)
{
	PawnOwner->SetActorLocation(NewPawnLoc);
}

void UPongMovementComponent::SetSpeed(float NewSpeed)
{
	PawnSpeed = NewSpeed;
}

void UPongMovementComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPongMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	

	if (PawnOwner->HasAuthority())
	{
		GEngine->AddOnScreenDebugMessage(-1,-1,FColor::White,FString::Printf(TEXT("Client Loc: %s"),*PawnOwner->GetActorLocation().ToString()));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1,-1,FColor::Green,FString::Printf(TEXT("Server Loc: %s"),*PawnOwner->GetActorLocation().ToString()));
	}
}

void UPongMovementComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ThisClass, PawnSpeed);
}

