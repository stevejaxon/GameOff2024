#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Tile/TileBase.h"

#include "MainGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class GAMEOFF2024_API AMainGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

private:
	int GridWidth{ 1 };
	int GridHeight{ 1 };
	int TotalTiles{ 1 };
	TArray<ATileBase*> GridStateRefs;

public:
	void Initialize(int Width, int Height);
	void AddToGridState(ATileBase&& Tile, int Index);
	void PopulateTilesNeighbors();
};
