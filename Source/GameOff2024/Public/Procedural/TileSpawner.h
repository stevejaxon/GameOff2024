#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Tile/TileContents.h"

#include "TileSpawner.generated.h"

UINTERFACE(MinimalAPI)
class UTileSpawner : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAMEOFF2024_API ITileSpawner
{
	GENERATED_BODY()

public:
	virtual void SpawnGrid(const int Rows, const int Columns, const TArray<TileContents> Tiles) {};
};
