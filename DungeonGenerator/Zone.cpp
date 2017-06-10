// Fill out your copyright notice in the Description page of Project Settings.

#include "Zone.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"

// Sets default values
AZone::AZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
    myBoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
}

// Called when the game starts or when spawned
void AZone::BeginPlay()
{
	Super::BeginPlay();
	
	zoneInfo.centerPoint = GetActorLocation();

	zoneInfo.topRightPoint = zoneInfo.centerPoint + myBoxCollider->GetScaledBoxExtent();
	zoneInfo.bottomLeftPoint = zoneInfo.centerPoint - myBoxCollider->GetScaledBoxExtent();
}

// Called every frame
void AZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

