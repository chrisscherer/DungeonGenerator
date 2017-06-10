// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DungeonGeneratorInfo.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct DUNGEONGENERATOR_API FDungeonGeneratorInfo
{
    GENERATED_BODY()
    
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Generator Settings")
    FVector minScale;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Generator Settings")
    FVector maxScale;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Generator Settings")
    FVector minLocation;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Generator Settings")
    FVector maxLocation;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Generator Settings")
    int32 numZones;
    
    FDungeonGeneratorInfo(){
        
    }
};
