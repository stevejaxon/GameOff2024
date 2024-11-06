#pragma once

#include "CoreMinimal.h"
#include "Tile/TileBase.h"
#include "Tile/HexagonalNeighbors.h"

#include "HexagonalTile.generated.h"

UCLASS()
class GAMEOFF2024_API AHexagonalTile : public ATileBase
{
	GENERATED_BODY()

private:
	FHexagonalNeighbors Neighbors;

public:	
	AHexagonalTile();
protected:
	virtual void BeginPlay() override;

	virtual void HandleMessage(ETileInteractionMessage Message) override;
	virtual void NotifyNeighbors(ETileInteractionMessage Message, int Distance) override;
public:	
	virtual void Tick(float DeltaTime) override;

	virtual const int NumberOfNeighbors() override;
	virtual const TArray<int> AdjacentTileIndices(const int TotalTiles, const int GridWidth) override;
	virtual void PopulateNeighbors(const TArray<ATileBase*>& NeighborRefs) override;

	virtual void HandleTileCursorBeginOver() override;
};
