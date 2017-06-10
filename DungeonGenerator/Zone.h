// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Structs/ZoneInfo.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"

#include "Zone.generated.h"

UCLASS()
class DUNGEONGENERATOR_API AZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings")
    FZoneInfo zoneInfo;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Collider")
    UBoxComponent* myBoxCollider;
    
};
