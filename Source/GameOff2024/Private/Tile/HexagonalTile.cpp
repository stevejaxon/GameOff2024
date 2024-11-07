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

	bool bIsEven{ TileIndex % 2 == 0 };
	bool bIsOnTopRow{ TileIndex >= TotalTiles - GridWidth };
	bool bIsOnBottomRow{ TileIndex < GridWidth };
	bool bIsOnLeftHandSide{ TileIndex % GridWidth == 0 };
	bool bIsOnRightHandSide{ (TileIndex + 1) % GridWidth == 0 };

	if (!bIsOnTopRow)
	{
		int NeighborIndex = TileIndex + GridWidth;
		NeighborsIndices.Insert(NeighborIndex, North);
	}

	if ((!bIsOnTopRow && !bIsOnRightHandSide) || (bIsOnTopRow && !bIsOnRightHandSide && bIsEven))
	{
		int NeighborIndex = bIsEven ? TileIndex + 1 : TileIndex + GridWidth + 1;
		NeighborsIndices.Insert(NeighborIndex, NorthEast);
	}

	if ((!bIsOnBottomRow && !bIsOnRightHandSide) || (bIsOnBottomRow && !bIsOnRightHandSide && !bIsEven))
	{
		int NeighborIndex = bIsEven ? TileIndex - (GridWidth - 1) : TileIndex + 1;
		NeighborsIndices.Insert(NeighborIndex, SouthEast);
	}

	if (!bIsOnBottomRow)
	{
		int NeighborIndex = TileIndex - GridWidth;
		NeighborsIndices.Insert(NeighborIndex, South);
	}

	if ((!bIsOnBottomRow && !bIsOnLeftHandSide) || (bIsOnBottomRow && !bIsOnLeftHandSide && !bIsEven))
	{
		int NeighborIndex{ bIsEven ? TileIndex - GridWidth - 1 : TileIndex - 1 };
		NeighborsIndices.Insert(NeighborIndex, SouthWest);
	}

	if ((!bIsOnTopRow && !bIsOnLeftHandSide) || (bIsOnTopRow && !bIsOnLeftHandSide && bIsEven))
	{
		int NeighborIndex{ bIsEven ? TileIndex - 1 : TileIndex + GridWidth - 1 };
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
	switch (Message)
	{
	case ETileInteractionMessage::BeginCursorOver:
		OnHighlightTileStart();
		break;
	case ETileInteractionMessage::EndCursorOver:
		OnHighlightTileEnd();
		break;
	case ETileInteractionMessage::RevealContents:
		break;
	case ETileInteractionMessage::Selected:
		break;
	default:
		break;
	}
	
}

const void AHexagonalTile::SendMessageToAllNeighbors(const ETileInteractionMessage Message)
{
	if (IsValid(Neighbors.North))
	{
		Neighbors.North->HandleMessage(Message);
	}
	if (IsValid(Neighbors.NorthEast))
	{
		Neighbors.NorthEast->HandleMessage(Message);
	}

	if (IsValid(Neighbors.SouthEast))
	{
		Neighbors.SouthEast->HandleMessage(Message);
	}

	if (IsValid(Neighbors.South))
	{
		Neighbors.South->HandleMessage(Message);
	}

	if (IsValid(Neighbors.SouthWest))
	{
		Neighbors.SouthWest->HandleMessage(Message);
	}

	if (IsValid(Neighbors.NorthWest))
	{
		Neighbors.NorthWest->HandleMessage(Message);
	}
}

void AHexagonalTile::NotifyNeighbors(ETileInteractionMessage Message, int Distance)
{
	SendMessageToAllNeighbors(Message);
}

void AHexagonalTile::HandleTileCursorOverBegin()
{
	NotifyNeighbors(ETileInteractionMessage::BeginCursorOver, 1);
}

void AHexagonalTile::HandleTileCursorOverEnd()
{
	NotifyNeighbors(ETileInteractionMessage::EndCursorOver, 1);
}
