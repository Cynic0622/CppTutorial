// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "MoveComponent.generated.h"


UCLASS( ClassGroup=(NewCppTutorial), meta=(BlueprintSpawnableComponent) )
class NEWCPPTUTORIAL_API UMoveComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMoveComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UPROPERTY(EditAnywhere)
	FVector MoveOffset;
	UPROPERTY(EditAnywhere)
	float Speed = 1.0f;
	float CurDistance;
	float MaxDistance;
	int MoveDirection = 1.f;
	FVector MoveOffsetNorm;
	FVector StartRelativeLocation;
};
