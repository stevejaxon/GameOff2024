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
	int TotalTiles{ 1 };
	TArray<ATileBase*> GridStateRefs;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) int GridWidth{ 1 };
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) int GridHeight{ 1 };

	void Initialize(int Width, int Height);
	void AddToGridState(ATileBase&& Tile, int Index);
	void PopulateTilesNeighbors();
};
