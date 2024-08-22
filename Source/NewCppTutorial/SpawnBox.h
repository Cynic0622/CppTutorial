// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "SpawnBox.generated.h"

UCLASS()
class NEWCPPTUTORIAL_API ASpawnBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnBox();

	UFUNCTION(BlueprintCallable)
	bool SpawnActor();
	UFUNCTION(BlueprintCallable)
	void EnableActorSpawning(bool Enable);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called when the actor stops playing
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	UFUNCTION()
	void SpawnActorScheduled();

	void ScheduleActorSpawn();
public:
	// actor class to spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> ActorClassToBeSpawned;
	
	// timing parameters
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AvgSpawnTime = 5.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RandomSpawnTimeOffset = 1.f;
private:
	// box in which will spawn actors
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* SpawnBox;

	// Helper for timing
	FTimerHandle SpawnTimerHandle;

	UPROPERTY(EditAnywhere)
	bool ShouldSpawn = true;
};
