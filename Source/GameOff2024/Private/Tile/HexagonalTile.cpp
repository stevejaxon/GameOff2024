#include "Tile/HexagonalTile.h"

const int NumNeighbors{ 6 };
const int North{ 0 };
const int NorthEast{ 1 };
const int SouthEast{ 2 };
const int South{ 3 };
const int SouthWest{ 4 };
const int NorthWest{ 5 };

AHexagonalTile::AHexagonalTile()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AHexagonalTile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHexagonalTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

const int AHexagonalTile::NumberOfNeighbors()
{
	return NumNeighbors;
}

const TArray<int> AHexagonalTile::AdjacentTileIndices(const int TotalTiles, const int GridWidth)
{
	TArray<int> NeighborsIndices;
	NeighborsIndices.Init(-1, 6);

	int LastIndex{ TotalTiles - 1 };
	bool bIsEven{ TileIndex % 2 == 0 };
	bool bIsOnTopRow{ TileIndex < GridWidth };
	bool bIsOnBottomRow{ TileIndex >= TotalTiles - GridWidth };
	bool bIsOnLeftHandSide{ TileIndex % GridWidth == 0 };
	bool bIsOnRightHandSide{ TileIndex + 1 % GridWidth == 0 };
	if (!bIsOnTopRow)
	{
		int NeighborIndex = TileIndex - GridWidth;
		NeighborsIndices.Insert(NeighborIndex, North);
	}

	if (!bIsOnTopRow || (!bIsOnRightHandSide && !bIsEven))
	{
		int NeighborIndex = bIsEven ? TileIndex - (GridWidth - 1) : TileIndex + 1;
		NeighborsIndices.Insert(NeighborIndex, NorthEast);
	}

	if (!bIsOnBottomRow || (!bIsOnRightHandSide && bIsEven))
	{
		int NeighborIndex = bIsEven ? TileIndex + 1 : TileIndex + GridWidth + 1;
		NeighborsIndices.Insert(NeighborIndex, SouthEast);
	}

	if (!bIsOnBottomRow)
	{
		int NeighborIndex = TileIndex + GridWidth;
		NeighborsIndices.Insert(NeighborIndex, South);
	}

	if (!bIsOnLeftHandSide && (!bIsOnBottomRow || !bIsEven))
	{
		int NeighborIndex{ bIsEven ? TileIndex - 1 : TileIndex + (GridWidth - 1) };
		NeighborsIndices.Insert(NeighborIndex, SouthEast);
	}

	if (!bIsOnLeftHandSide && (!bIsOnTopRow || !bIsEven))
	{
		int NeighborIndex{ bIsEven ? TileIndex - GridWidth - 1 : TileIndex - 1 };
		NeighborsIndices.Insert(NeighborIndex, NorthWest);
	}

	return NeighborsIndices;
}

void AHexagonalTile::PopulateNeighbors(const TArray<ATileBase*>& NeighborRefs)
{
	if (NeighborRefs.Num() != NumNeighbors) {
		return;
	}

	Neighbors.North = Cast<AHexagonalTile>(NeighborRefs[North]);
	Neighbors.NorthEast = Cast<AHexagonalTile>(NeighborRefs[NorthEast]);
	Neighbors.SouthEast = Cast<AHexagonalTile>(NeighborRefs[SouthEast]);
	Neighbors.South = Cast<AHexagonalTile>(NeighborRefs[South]);
	Neighbors.SouthWest = Cast<AHexagonalTile>(NeighborRefs[SouthWest]);
	Neighbors.NorthWest = Cast<AHexagonalTile>(NeighborRefs[NorthWest]);
}

void AHexagonalTile::HandleMessage(ETileInteractionMessage Message)
{
	OnHighlightTileStart();
}

void AHexagonalTile::NotifyNeighbors(ETileInteractionMessage Message, int Distance)
{
	if (IsValid(Neighbors.North))
	{
		Neighbors.North->HandleMessage(ETileInteractionMessage::BeginCursorOver);
	}
	if (IsValid(Neighbors.NorthEast))
	{
		Neighbors.NorthEast->HandleMessage(ETileInteractionMessage::BeginCursorOver);
	}

	if (IsValid(Neighbors.SouthEast))
	{
		Neighbors.SouthEast->HandleMessage(ETileInteractionMessage::BeginCursorOver);
	}

	if (IsValid(Neighbors.South))
	{
		Neighbors.South->HandleMessage(ETileInteractionMessage::BeginCursorOver);
	}

	if (IsValid(Neighbors.SouthWest))
	{
		Neighbors.SouthWest->HandleMessage(ETileInteractionMessage::BeginCursorOver);
	}

	if (IsValid(Neighbors.NorthWest))
	{
		Neighbors.NorthWest->HandleMessage(ETileInteractionMessage::BeginCursorOver);
	}
	
}

void AHexagonalTile::HandleTileCursorBeginOver()
{
	NotifyNeighbors(ETileInteractionMessage::BeginCursorOver, 1);
}
