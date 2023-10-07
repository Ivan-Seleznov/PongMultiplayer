// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Components/PongMovementComponent.h"

#include "Components/ShapeComponent.h"
#include "Net/UnrealNetwork.h"
#include "Pawns/BasePawn.h"

float HM_MACRO_DURATION = 3.f;
#define SLOG(x,c) GEngine->AddOnScreenDebugMessage(-1,HM_MACRO_DURATION,c,x);

FPawnSavedMove::FPawnSavedMove():DeltaTime(0.f)
{
}

FPawnSavedMove::FPawnSavedMove(FVector PawnLoc,FVector Acceleration,float Delta) : PawnLoc(PawnLoc), ControlAcceleration(Acceleration), DeltaTime(Delta)
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

void UPongMovementComponent::MovePawn(const FVector& ControlAcceleration, float DeltaTime)
{
	const FVector DeltaLocation = ControlAcceleration * (PawnSpeed * DeltaTime);
	const FVector NewPawnLocation = BasePawnOwner->GetShapeComponent()->GetComponentLocation() + DeltaLocation;
	
	BasePawnOwner->GetShapeComponent()->SetWorldLocation(NewPawnLocation,true);
	
	if (!PawnOwner->HasAuthority())
	{
		FPawnSavedMove PawnSavedMove(NewPawnLocation,ControlAcceleration,DeltaTime);
		Server_MovePawn(PawnSavedMove);
	}
}

void UPongMovementComponent::Server_MovePawn_Implementation(const FPawnSavedMove& PawnSavedMove)
{
	const FVector DeltaLocation = PawnSavedMove.ControlAcceleration * (PawnSpeed * PawnSavedMove.DeltaTime);
	const FVector NewPawnLocation = BasePawnOwner->GetShapeComponent()->GetComponentLocation() + DeltaLocation;
	
	if (PawnSavedMove.PawnLoc == NewPawnLocation)
	{
		BasePawnOwner->GetShapeComponent()->SetWorldLocation(NewPawnLocation,true);
	}
	else
	{
		Client_CorrectPawnMove(BasePawnOwner->GetShapeComponent()->GetComponentLocation());
	}
}

void UPongMovementComponent::Client_CorrectPawnMove_Implementation(const FVector& NewPawnLoc)
{
	BasePawnOwner->GetShapeComponent()->SetWorldLocation(NewPawnLoc,true);
}

void UPongMovementComponent::SetSpeed(float NewSpeed)
{
	PawnSpeed = NewSpeed;
}

void UPongMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (BasePawnOwner->IsLocallyControlled() && !BasePawnOwner->HasAuthority())
	{
		const FVector ControlAcceleration = GetPendingInputVector().GetClampedToMaxSize(1.f);
		MovePawn(ControlAcceleration,DeltaTime);
		
		ConsumeInputVector();
	}
	
	/*if (PawnOwner->HasAuthority())
	{
		GEngine->AddOnScreenDebugMessage(-1,-1,FColor::White,FString::Printf(TEXT("Client Loc: %s"),*PawnOwner->GetActorLocation().ToString()));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1,-1,FColor::Green,FString::Printf(TEXT("Server Loc: %s"),*PawnOwner->GetActorLocation().ToString()));
	}*/
}

void UPongMovementComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ThisClass, PawnSpeed);
}

