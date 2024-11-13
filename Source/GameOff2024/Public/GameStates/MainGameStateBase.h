#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Tile/TileBase.h"
#include "Tile/TileContents.h"
#include "Procedural/TileGridConfiguration.h"

#include "MainGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class GAMEOFF2024_API AMainGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

private:
	int TotalTiles{ 1 };
	TArray<ATileBase*> GridStateRefs;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) FTileGridConfiguration LevelConfig;

	void Initialize(FTileGridConfiguration&& Config);
	void AddToGridState(ATileBase&& Tile, int Index);
	void PopulateTilesNeighbors();
};
