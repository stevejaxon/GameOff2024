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

const void AHexagonalTile::TransmitMessageInDirection(const ETileInteractionMessage Message, TSet<int>& VisitedNeighbors, const UEHexNeighborDirection Direction, const int Distance, AHexagonalTile* Neighbor1, AHexagonalTile* Neighbor2, AHexagonalTile* Neighbor3)
{
	if (IsValid(Neighbor1) && !VisitedNeighbors.Contains(Neighbor1->TileIndex))
	{
		Neighbor1->HandleMessage(Message, VisitedNeighbors, Direction, Distance);
	}
	if (IsValid(Neighbor2) && !VisitedNeighbors.Contains(Neighbor2->TileIndex))
	{
		Neighbor2->HandleMessage(Message, VisitedNeighbors, Direction, Distance);
	}
	if (IsValid(Neighbor3) && !VisitedNeighbors.Contains(Neighbor3->TileIndex))
	{
		Neighbor3->HandleMessage(Message, VisitedNeighbors, Direction, Distance);
	}
}

const void AHexagonalTile::HandleMessage(const ETileInteractionMessage Message, TSet<int>& VisitedNeighbors, const UEHexNeighborDirection Direction, const int Distance)
{
	HandleMessage(Message);
	VisitedNeighbors.Add(TileIndex);
	if (Distance <= 0)
	{
		return;
	}
	int RemainingDistance{ Distance - 1 };
	switch (Direction)
	{
	case UEHexNeighborDirection::North:
		TransmitMessageInDirection(Message, VisitedNeighbors, Direction, RemainingDistance, Neighbors.North, Neighbors.NorthEast, Neighbors.NorthWest);
		break;
	case UEHexNeighborDirection::NorthEast:
		TransmitMessageInDirection(Message, VisitedNeighbors, Direction, RemainingDistance, Neighbors.NorthEast, Neighbors.SouthEast, Neighbors.North);
		break;
	case UEHexNeighborDirection::SouthEast:
		TransmitMessageInDirection(Message, VisitedNeighbors, Direction, RemainingDistance, Neighbors.SouthEast, Neighbors.South, Neighbors.NorthEast);
		break;
	case UEHexNeighborDirection::South:
		TransmitMessageInDirection(Message, VisitedNeighbors, Direction, RemainingDistance, Neighbors.South, Neighbors.SouthEast, Neighbors.SouthWest);
		break;
	case UEHexNeighborDirection::SouthWest:
		TransmitMessageInDirection(Message, VisitedNeighbors, Direction, RemainingDistance, Neighbors.SouthWest, Neighbors.NorthWest, Neighbors.South);
		break;
	case UEHexNeighborDirection::NorthWest:
		TransmitMessageInDirection(Message, VisitedNeighbors, Direction, RemainingDistance, Neighbors.NorthWest, Neighbors.North, Neighbors.SouthWest);
		break;
	default:
		break;
	}

}

void AHexagonalTile::NotifyNeighbors(ETileInteractionMessage Message, int Distance)
{
	TSet<int> VisitedNeighbors;
	VisitedNeighbors.Add(TileIndex);
	int RemainingDistance{ Distance - 1 };
	if (IsValid(Neighbors.North))
	{
		Neighbors.North->HandleMessage(Message, VisitedNeighbors, UEHexNeighborDirection::North, RemainingDistance);
	}
	if (IsValid(Neighbors.NorthEast))
	{
		Neighbors.NorthEast->HandleMessage(Message, VisitedNeighbors, UEHexNeighborDirection::NorthEast, RemainingDistance);
	}
	if (IsValid(Neighbors.SouthEast))
	{
		Neighbors.SouthEast->HandleMessage(Message, VisitedNeighbors, UEHexNeighborDirection::SouthEast, RemainingDistance);
	}
	if (IsValid(Neighbors.South))
	{
		Neighbors.South->HandleMessage(Message, VisitedNeighbors, UEHexNeighborDirection::South, RemainingDistance);
	}
	if (IsValid(Neighbors.SouthWest))
	{
		Neighbors.SouthWest->HandleMessage(Message, VisitedNeighbors, UEHexNeighborDirection::SouthWest, RemainingDistance);
	}
	if (IsValid(Neighbors.NorthWest))
	{
		Neighbors.NorthWest->HandleMessage(Message, VisitedNeighbors, UEHexNeighborDirection::NorthWest, RemainingDistance);
	}
}

void AHexagonalTile::HandleTileCursorOverBegin()
{
	NotifyNeighbors(ETileInteractionMessage::BeginCursorOver, 1);
}

void AHexagonalTile::HandleTileCursorOverEnd()
{
	NotifyNeighbors(ETileInteractionMessage::EndCursorOver, 1);
}
