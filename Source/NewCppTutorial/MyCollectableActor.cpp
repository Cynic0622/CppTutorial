// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCollectableActor.h"

#include "Components/BoxComponent.h"

// Sets default values
AMyCollectableActor::AMyCollectableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	if (StaticMesh)
	{
		RootComponent = StaticMesh;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("StaticMesh component failed to create!"));
	}
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(StaticMesh);
}

// Called when the game starts or when spawned
void AMyCollectableActor::BeginPlay()
{
	Super::BeginPlay();

	FScriptDelegate DelegateSubscriber;
	DelegateSubscriber.BindUFunction(this, "OnComponentBeginOverlap");
	BoxCollision->OnComponentBeginOverlap.Add(DelegateSubscriber);
	
}

void AMyCollectableActor::OnComponentBeginOverlap(UBoxComponent* Component, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsLaunch && OtherActor->IsA(TriggerClass))
	{
		OnJumpTrigger.Broadcast(OtherActor, Component);
	}
}

// Called every frame
void AMyCollectableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsLaunch)
	{
		LiveTime -= DeltaTime;
		if (LiveTime <= 0.f)
		{
			Destroy();
		}
	}

}

void AMyCollectableActor::Jump(float Newvelocity)
{
	// auto NewLocation = GetActorLocation();
	// NewLocation.Z += velocity;
	// SetActorLocation(NewLocation);
	if (!IsLaunch)
	{
		StaticMesh->AddImpulse({ 0.f, 0.f, Newvelocity * 500.f });
		IsLaunch = true;
	}
	
}

