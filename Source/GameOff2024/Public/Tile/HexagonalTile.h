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

	const void HandleMessage(const ETileInteractionMessage Message, const ETileInteractionAction NotifyPattern, TSet<int>& VisitedNeighbors, const UEHexNeighborDirection Direction, const ETileInteractionFeedback Feedback, const int Distance);
	template<typename... Args>
	const void TransmitMessageInDirection(const ETileInteractionMessage Message, const ETileInteractionAction NotifyPattern, TSet<int>& VisitedNeighbors, const UEHexNeighborDirection Direction, const ETileInteractionFeedback Feedback, const int Distance, Args*... Neighbors);
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

	virtual const void HandleMessage(const ETileInteractionMessage Message, const ETileInteractionFeedback Feedback) override;
	virtual const void NotifyNeighbors(const ETileInteractionMessage Message, const ETileInteractionAction NotifyPattern, const ETileInteractionFeedback Feedback, const int Distance) override;
public:	
	virtual void Tick(float DeltaTime) override;

	virtual const int NumberOfNeighbors() override;
	virtual const TArray<int> AdjacentTileIndices(const int TotalTiles, const int GridWidth) override;
	virtual void PopulateNeighbors(const TArray<ATileBase*>& NeighborRefs) override;

	virtual void HandleTileCursorOverBegin(const ETileInteractionAction NotifyPattern, const ETileInteractionFeedback Feedback, const int NotifyDistance) override;
	virtual void HandleTileCursorOverEnd(const ETileInteractionAction NotifyPattern, const int NotifyDistance) override;
};