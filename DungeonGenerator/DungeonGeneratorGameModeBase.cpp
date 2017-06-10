// Fill out your copyright notice in the Description page of Project Settings.

#include "DungeonGeneratorGameModeBase.h"
#include "Zone.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include <time.h>

ADungeonGeneratorGameModeBase::ADungeonGeneratorGameModeBase()
{
    srand(time(nullptr));
}

void ADungeonGeneratorGameModeBase::BeginPlay()
{
    Super::BeginPlay();
    
    UWorld* const World = GetWorld();
    
    for(int i=0;i<myInfo.numZones;i++){
        if (World != nullptr)
        {
			FTransform newZoneTransform = FTransform(GenerateRandomLocation());

			AZone* temp = World->SpawnActorDeferred<AZone>(zoneSubclass, newZoneTransform, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding);
            temp->SetActorScale3D(GenerateRandomScale());
			temp->FinishSpawning(newZoneTransform);

			gameZones.Add(temp);
        }
    }

	SeparateZones();
}

FVector ADungeonGeneratorGameModeBase::GenerateRandomLocation() const
{
    int randomX = rand() %  int(myInfo.maxLocation.X) + int(myInfo.minLocation.X);
    int randomY = rand() %  int(myInfo.maxLocation.Y) + int(myInfo.minLocation.Y);
    int randomZ = rand() %  int(myInfo.maxLocation.Z) + int(myInfo.minLocation.Z);
    
    return FVector(randomX, randomY, randomZ);
}

FVector ADungeonGeneratorGameModeBase::GenerateRandomScale() const
{
    int randomX = rand() %  int(myInfo.maxScale.X) + int(myInfo.minScale.X);
    int randomY = rand() %  int(myInfo.maxScale.Y) + int(myInfo.minScale.Y);
    int randomZ = rand() %  int(myInfo.maxScale.Z) + int(myInfo.minScale.Z);
    
    return FVector(randomX, randomY, randomZ);
}

void ADungeonGeneratorGameModeBase::SeparateZones()
{
	for(int i=0;i<gameZones.Num(); i++)
	{
		for(int j=i+1;j<gameZones.Num(); j++)
		{
			AZone* zone1 = gameZones[i];
			AZone* zone2 = gameZones[j];

			FVector edgeOffset = checkForEdgeOverlap(zone1, zone2);
			FVector centerOffset = checkForCenterOverlap(zone1, zone2);

			FMath math = FMath();

			float xToUse = math.Max(math.Abs(edgeOffset.X), math.Abs(centerOffset.X));
			float yToUse = math.Max(math.Abs(edgeOffset.Y), math.Abs(centerOffset.Y));
			float zToUse = math.Max(math.Abs(edgeOffset.Z), math.Abs(centerOffset.Z));

			FVector newOffset = FVector(
				xToUse,
				yToUse,
				zone2->zoneInfo.centerPoint.Z
			);

			FVector newZone2Location = zone2->GetActorLocation() + newOffset;

			zone2->SetActorLocation(newZone2Location);
		}
	}
}

FVector ADungeonGeneratorGameModeBase::checkForCenterOverlap(AZone* zone1, AZone* zone2)
{
	FVector zone2CenterPoint = zone2->GetActorLocation();
	FVector finalOffsetNeeded = FVector(0);

	finalOffsetNeeded.X = calculateRequiredCenterOffset(zone1->zoneInfo.topRightPoint.X, zone1->zoneInfo.bottomLeftPoint.X, zone2CenterPoint.X);
	finalOffsetNeeded.Y = calculateRequiredCenterOffset(zone1->zoneInfo.topRightPoint.Y, zone1->zoneInfo.bottomLeftPoint.Y, zone2CenterPoint.Y);
	finalOffsetNeeded.Z = calculateRequiredCenterOffset(zone1->zoneInfo.topRightPoint.Z, zone1->zoneInfo.bottomLeftPoint.Z, zone2CenterPoint.Z);

	return finalOffsetNeeded;
}

FVector ADungeonGeneratorGameModeBase::checkForEdgeOverlap(AZone* zone1, AZone* zone2)
{
	FVector finalOffsetNeeded = FVector(0);

	finalOffsetNeeded.X = calculateRequiredEdgeOffset(zone1->zoneInfo.topRightPoint.X, zone1->zoneInfo.bottomLeftPoint.X, zone2->zoneInfo.topRightPoint.X, zone2->zoneInfo.bottomLeftPoint.X);
	finalOffsetNeeded.Y = calculateRequiredEdgeOffset(zone1->zoneInfo.topRightPoint.Y, zone1->zoneInfo.bottomLeftPoint.Y, zone2->zoneInfo.topRightPoint.Y, zone2->zoneInfo.bottomLeftPoint.Y);
	finalOffsetNeeded.Z = calculateRequiredEdgeOffset(zone1->zoneInfo.topRightPoint.Z, zone1->zoneInfo.bottomLeftPoint.Z, zone2->zoneInfo.topRightPoint.Z, zone2->zoneInfo.bottomLeftPoint.Z);

	return finalOffsetNeeded;
}

float ADungeonGeneratorGameModeBase::calculateRequiredCenterOffset(float low1, float high1, float mid2)
{
	FMath math = FMath();

	float min1 = math.Min(low1, high1);
	float max1 = math.Max(low1, high1);

	if (max1 < mid2 && min1 > mid2)
	{
		float dist1 = mid2 - min1;
		float dist2 = max1 - mid2;

		if (dist2 < dist1)
		{
			return dist2 * -1;
		}
			return dist1;
	}
	return 0.0f;
}

float ADungeonGeneratorGameModeBase::calculateRequiredEdgeOffset(float low1, float high1, float low2, float high2)
{
	FMath math = FMath();

	float min1 = math.Min(low1, high1);
	float max1 = math.Max(low1, high1);

	float min2 = math.Min(low2, high2);
	float max2 = math.Max(low2, high2);

	if ((max1 >= min2) && (min1 <= max2))
	{
		float dist1 = max2 - min1;
		float dist2 = max1 - min2;

		if (dist2 < dist1)
		{
			return dist2 * -1;
		}
		return dist1;
	}
	return 0.0f;
}