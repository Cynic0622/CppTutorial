// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveComponent.h"

// Sets default values for this component's properties
UMoveComponent::UMoveComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
/**
 * 
 */
void UMoveComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	StartRelativeLocation = GetRelativeLocation();
	MoveOffsetNorm = MoveOffset;
	MoveOffsetNorm.Normalize();
	MaxDistance = MoveOffset.Length();

	

}


// Called every frame
void UMoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	if (MoveEnable)
	{
		CurDistance += DeltaTime * Speed * MoveDirection;
		if (CurDistance >= MaxDistance || CurDistance <= 0.f)
		{
			MoveDirection *= -1.f;
			OnEndpointReached.Broadcast(CurDistance >= MaxDistance);
			CurDistance = FMath::Clamp(CurDistance, 0.0f, MaxDistance);
		}
			
	}
	SetRelativeLocation(StartRelativeLocation + MoveOffsetNorm * CurDistance);
}

void UMoveComponent::EnableMovement(bool ShouldMove)
{
	MoveEnable = ShouldMove;
	// check if ticking is required
	SetComponentTickEnabled(MoveEnable);
}

void UMoveComponent::ResetMovement()
{
	CurDistance = 0.0f;
	SetRelativeLocation(StartRelativeLocation);
}

void UMoveComponent::SetMovementDirection(int Direction)
{
	MoveDirection = Direction >= 1 ? 1 : -1;
}

