#pragma once

#include "CoreMinimal.h"

#include "HexagonalNeighbors.generated.h"

class AHexagonalTile;
/**
 * 
 */
USTRUCT(BlueprintType)
struct GAMEOFF2024_API FHexagonalNeighbors
{
	GENERATED_BODY()

public:
	AHexagonalTile* North;
	AHexagonalTile* NorthEast;
	AHexagonalTile* NorthWest;
	AHexagonalTile* South;
	AHexagonalTile* SouthEast;
	AHexagonalTile* SouthWest;
};
