#pragma once

#include "CoreMinimal.h"
#include "Tile/TileContents.h"


#include "TileGridConfiguration.generated.h"
/**
 * 
 */
USTRUCT(BlueprintType)
struct GAMEOFF2024_API FTileGridConfiguration
{
public:
	GENERATED_BODY()

	int GridWidth;
	int GridHeight;
	int GoalAmount;
	TArray<int> GoalLocations;
	TArray<FTileContents> GridContents;
};
