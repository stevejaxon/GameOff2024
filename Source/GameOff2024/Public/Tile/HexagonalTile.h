#pragma once

#include "CoreMinimal.h"
#include "Tile/TileBase.h"
#include "Tile/HexagonalNeighbors.h"
#include "Tile/EHexNeighborDirection.h"

#include "HexagonalTile.generated.h"

UCLASS()
class GAMEOFF2024_API AHexagonalTile : public ATileBase
{
	GENERATED_BODY()

private:
	FHexagonalNeighbors Neighbors;

	const void HandleMessage(const ETileInteractionMessage Message, TSet<int>& VisitedNeighbors, const UEHexNeighborDirection Direction, const int Distance);
	const void TransmitMessageInDirection(const ETileInteractionMessage Message, TSet<int>& VisitedNeighbors, const UEHexNeighborDirection Direction, const int Distance, AHexagonalTile* Neighbor1, AHexagonalTile* Neighbor2, AHexagonalTile* Neighbor3);
	const int NorthernAdjacentTileIndex(const int Index, const int GridWidth, const bool bIsOnTopRow);
	const int NorthEasternAdjacentTileIndex(const int Index, const int GridWidth, const bool bIsOnTopRow, const bool bIsEvenRow, const bool bIsOnRightHandSide);
	const int SouthEasternAdjacentTileIndex(const int Index, const int GridWidth, const bool bIsOnBottomRow, const bool bIsEvenRow, const bool bIsOnRightHandSide);
	const int SouthernAdjacentTileIndex(const int Index, const int GridWidth, const bool bIsOnBottomRow);
	const int SouthWesternAdjacentTileIndex(const int Index, const int GridWidth, const bool bIsOnBottomRow, const bool bIsEvenRow, const bool bIsOnLeftHandSide);
	const int NorthWesternAdjacentTileIndex(const int Index, const int GridWidth, const bool bIsOnTopRow, const bool bIsEvenRow, const bool bIsOnLeftHandSide);

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

	virtual void HandleTileCursorOverBegin() override;
	virtual void HandleTileCursorOverEnd() override;
};
