// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Structs/DungeonGeneratorInfo.h"
#include "Zone.h"

#include "DungeonGeneratorGameModeBase.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class DUNGEONGENERATOR_API ADungeonGeneratorGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
    ADungeonGeneratorGameModeBase();
    
protected:
    virtual void BeginPlay() override;
    
    FVector GenerateRandomLocation() const;
    
    FVector GenerateRandomScale() const;

	void SeparateZones();

	static FVector checkForCenterOverlap(AZone* zone1, AZone* zone2);

	static FVector checkForEdgeOverlap(AZone* zone1, AZone* zone2);

	static float calculateRequiredCenterOffset(float low1, float high1, float mid2);

	static float calculateRequiredEdgeOffset(float low1, float high1, float low2, float high2);

	TArray<AZone*> gameZones;
    
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings")
    FDungeonGeneratorInfo myInfo;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings")
    TSubclassOf<class AZone> zoneSubclass;

};
