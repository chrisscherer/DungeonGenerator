// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ZoneInfo.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct DUNGEONGENERATOR_API FZoneInfo
{
    GENERATED_BODY()
    
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings")
    FVector lengthWidthHeight;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings")
    FVector centerPoint;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings")
    FVector topRightPoint;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings")
    FVector bottomLeftPoint;
    
    FZoneInfo(){
        
    }
};
