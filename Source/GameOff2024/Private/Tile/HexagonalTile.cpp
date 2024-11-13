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

const int AHexagonalTile::NorthernAdjacentTileIndex(const int Index, const int GridWidth, const bool bIsOnTopRow)
{
	if (bIsOnTopRow)
	{
		return -1;
	}
	return Index + GridWidth;
}

const int AHexagonalTile::NorthEasternAdjacentTileIndex(const int Index, const int GridWidth, const bool bIsOnTopRow, const bool bIsEvenRow, const bool bIsOnRightHandSide)
{
	if (bIsOnRightHandSide)
	{
		return -1;
	}
	if (bIsEvenRow)
	{
		return Index + 1;
	}
	if (bIsOnTopRow)
	{
		return -1;
	}
	return Index + GridWidth + 1;
}

const int AHexagonalTile::SouthEasternAdjacentTileIndex(const int Index, const int GridWidth, const bool bIsOnBottomRow, const bool bIsEvenRow, const bool bIsOnRightHandSide)
{
	if (bIsOnRightHandSide)
	{
		return -1;
	}
	if (!bIsEvenRow)
	{
		return Index + 1;
	}
	if (bIsOnBottomRow)
	{
		return -1;
	}
	return Index - (GridWidth - 1);
}

const int AHexagonalTile::SouthernAdjacentTileIndex(const int Index, const int GridWidth, const bool bIsOnBottomRow)
{
	if (bIsOnBottomRow)
	{
		return -1;
	}
	return Index - GridWidth;
}

const int AHexagonalTile::SouthWesternAdjacentTileIndex(const int Index, const int GridWidth, const bool bIsOnBottomRow, const bool bIsEvenRow, const bool bIsOnLeftHandSide)
{
	if (bIsOnLeftHandSide)
	{
		return -1;
	}
	if (!bIsEvenRow)
	{
		return Index - 1;
	}
	if (bIsOnBottomRow)
	{
		return -1;
	}
	return Index - (GridWidth + 1);
}

const int AHexagonalTile::NorthWesternAdjacentTileIndex(const int Index, const int GridWidth, const bool bIsOnTopRow, const bool bIsEvenRow, const bool bIsOnLeftHandSide)
{
	if (bIsOnLeftHandSide)
	{
		return -1;
	}
	if (bIsEvenRow)
	{
		return Index - 1;
	}
	if (bIsOnTopRow)
	{
		return -1;
	}
	return Index + (GridWidth - 1);
}

const TArray<int> AHexagonalTile::AdjacentTileIndices(const int TotalTiles, const int GridWidth)
{
	TArray<int> NeighborsIndices;
	NeighborsIndices.Init(-1, 6);

	bool bIsEvenRow{ (TileIndex % GridWidth) % 2 == 0 };
	bool bIsOnTopRow{ TileIndex >= TotalTiles - GridWidth };
	bool bIsOnBottomRow{ TileIndex < GridWidth };
	bool bIsOnLeftHandSide{ TileIndex % GridWidth == 0 };
	bool bIsOnRightHandSide{ (TileIndex + 1) % GridWidth == 0 };

	NeighborsIndices.Insert(NorthernAdjacentTileIndex(TileIndex, GridWidth, bIsOnTopRow), North);
	NeighborsIndices.Insert(NorthEasternAdjacentTileIndex(TileIndex, GridWidth, bIsOnTopRow, bIsEvenRow, bIsOnRightHandSide), NorthEast);
	NeighborsIndices.Insert(SouthEasternAdjacentTileIndex(TileIndex, GridWidth, bIsOnBottomRow, bIsEvenRow, bIsOnRightHandSide), SouthEast);
	NeighborsIndices.Insert(SouthernAdjacentTileIndex(TileIndex, GridWidth, bIsOnBottomRow), South);
	NeighborsIndices.Insert(SouthWesternAdjacentTileIndex(TileIndex, GridWidth, bIsOnBottomRow, bIsEvenRow, bIsOnLeftHandSide), SouthWest);
	NeighborsIndices.Insert(NorthWesternAdjacentTileIndex(TileIndex, GridWidth, bIsOnTopRow, bIsEvenRow, bIsOnLeftHandSide), NorthEast);

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
