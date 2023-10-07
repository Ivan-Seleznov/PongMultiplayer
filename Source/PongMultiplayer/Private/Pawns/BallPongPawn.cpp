// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/BallPongPawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"

ABallPongPawn::ABallPongPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	ShapeComponent = CreateDefaultSubobject<UCapsuleComponent>("Capsule Collision");
	RootComponent = ShapeComponent;

	PawnMesh->SetupAttachment(RootComponent);

	ShapeComponent->OnComponentHit.AddDynamic(this,&ThisClass::OnBallHit);
}

void ABallPongPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	SetActorLocation(GetActorLocation() + BallVelocity * BallSpeed * DeltaSeconds,true);
}

void ABallPongPawn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass,BallVelocity);
	DOREPLIFETIME(ThisClass,BallSpeed);

}

void ABallPongPawn::BeginPlay()
{
	Super::BeginPlay();
	
	if (HasAuthority())
	{
		BallSpawnLocation = GetActorLocation();
		
		int32 RandomX = FMath::RandRange(0, 1);
		int32 RandomY = FMath::RandRange(0, 1);

		BallVelocity = FVector(RandomX == 0 ? -1 : 1, RandomY == 0 ? -1 : 1, 0);
	}
}

void ABallPongPawn::OnBallHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if (HasAuthority())
	{
		BallVelocity = UKismetMathLibrary::GetReflectionVector(BallVelocity, Hit.ImpactNormal);
		BallVelocity.Z = 0;
	}
}
