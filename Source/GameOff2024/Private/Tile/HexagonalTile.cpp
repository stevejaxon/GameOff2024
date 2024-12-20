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
	NeighborsIndices.Insert(NorthWesternAdjacentTileIndex(TileIndex, GridWidth, bIsOnTopRow, bIsEvenRow, bIsOnLeftHandSide), NorthWest);

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

const void AHexagonalTile::HandleMessage(const ETileInteractionMessage Message, const UETileType HoveredTileType, const ETileInteractionFeedback Feedback, const FLinearColor FeedbackColor)
{
	switch (Message)
	{
	case ETileInteractionMessage::BeginCursorOver:
		OnHighlightTileStart(HoveredTileType, Feedback, FeedbackColor);
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

template<typename ...Args>
const void AHexagonalTile::TransmitMessageInDirection(const ETileInteractionMessage Message, const ETileInteractionAction NotifyPattern, const UETileType HoveredTileType, TSet<int>& VisitedNeighbors, const UEHexNeighborDirection Direction, const ETileInteractionFeedback Feedback, const FLinearColor FeedbackColor, const int Distance, Args * ...Neighbors)
{
	TArray<AHexagonalTile*> NeighborsArray = TArray<AHexagonalTile*>{ Neighbors... };
	for (AHexagonalTile* Neighbor : NeighborsArray)
	{
		if (IsValid(Neighbor) && !VisitedNeighbors.Contains(Neighbor->TileIndex))
		{
			Neighbor->HandleMessage(Message, NotifyPattern, HoveredTileType, VisitedNeighbors, Direction, Feedback, FeedbackColor, Distance);
		}
	}
}

const void AHexagonalTile::HandleMessage(const ETileInteractionMessage Message, const ETileInteractionAction NotifyPattern, const UETileType HoveredTileType, TSet<int>& VisitedNeighbors, const UEHexNeighborDirection Direction, const ETileInteractionFeedback Feedback, const FLinearColor FeedbackColor, const int Distance)
{
	HandleMessage(Message, HoveredTileType, Feedback, FeedbackColor);
	VisitedNeighbors.Add(TileIndex);
	if (Distance <= 0)
	{
		return;
	}
	int RemainingDistance{ Distance - 1 };
	switch (Direction)
	{
	case UEHexNeighborDirection::North:
		if (NotifyPattern == ETileInteractionAction::NotifyNeighborsDirectionally)
		{
			TransmitMessageInDirection(Message, NotifyPattern, HoveredTileType, VisitedNeighbors, Direction, Feedback, FeedbackColor, RemainingDistance, Neighbors.North);
		}
		else
		{
			TransmitMessageInDirection(Message, NotifyPattern, HoveredTileType, VisitedNeighbors, Direction, Feedback, FeedbackColor, RemainingDistance, Neighbors.North, Neighbors.NorthEast, Neighbors.NorthWest);
		}
		break;
	case UEHexNeighborDirection::NorthEast:
		if (NotifyPattern == ETileInteractionAction::NotifyNeighborsDirectionally)
		{
			TransmitMessageInDirection(Message, NotifyPattern, HoveredTileType, VisitedNeighbors, Direction, Feedback, FeedbackColor, RemainingDistance, Neighbors.NorthEast);
		}
		else
		{
			TransmitMessageInDirection(Message, NotifyPattern, HoveredTileType, VisitedNeighbors, Direction, Feedback, FeedbackColor, RemainingDistance, Neighbors.NorthEast, Neighbors.SouthEast, Neighbors.North);
		}
		break;
	case UEHexNeighborDirection::SouthEast:
		if (NotifyPattern == ETileInteractionAction::NotifyNeighborsDirectionally)
		{
			TransmitMessageInDirection(Message, NotifyPattern, HoveredTileType, VisitedNeighbors, Direction, Feedback, FeedbackColor, RemainingDistance, Neighbors.SouthEast);
		}
		else
		{
			TransmitMessageInDirection(Message, NotifyPattern, HoveredTileType, VisitedNeighbors, Direction, Feedback, FeedbackColor, RemainingDistance, Neighbors.SouthEast, Neighbors.South, Neighbors.NorthEast);
		}
		break;
	case UEHexNeighborDirection::South:
		if (NotifyPattern == ETileInteractionAction::NotifyNeighborsDirectionally)
		{
			TransmitMessageInDirection(Message, NotifyPattern, HoveredTileType, VisitedNeighbors, Direction, Feedback, FeedbackColor, RemainingDistance, Neighbors.South);
		}
		else
		{
			TransmitMessageInDirection(Message, NotifyPattern, HoveredTileType, VisitedNeighbors, Direction, Feedback, FeedbackColor, RemainingDistance, Neighbors.South, Neighbors.SouthEast, Neighbors.SouthWest);
		}
		break;
	case UEHexNeighborDirection::SouthWest:
		if (NotifyPattern == ETileInteractionAction::NotifyNeighborsDirectionally)
		{
			TransmitMessageInDirection(Message, NotifyPattern, HoveredTileType, VisitedNeighbors, Direction, Feedback, FeedbackColor, RemainingDistance, Neighbors.SouthWest);
		}
		else
		{
			TransmitMessageInDirection(Message, NotifyPattern, HoveredTileType, VisitedNeighbors, Direction, Feedback, FeedbackColor, RemainingDistance, Neighbors.SouthWest, Neighbors.NorthWest, Neighbors.South);
		}
		break;
	case UEHexNeighborDirection::NorthWest:
		if (NotifyPattern == ETileInteractionAction::NotifyNeighborsDirectionally)
		{
			TransmitMessageInDirection(Message, NotifyPattern, HoveredTileType, VisitedNeighbors, Direction, Feedback, FeedbackColor, RemainingDistance, Neighbors.NorthWest);
		}
		else
		{
			TransmitMessageInDirection(Message, NotifyPattern, HoveredTileType, VisitedNeighbors, Direction, Feedback, FeedbackColor, RemainingDistance, Neighbors.NorthWest, Neighbors.North, Neighbors.SouthWest);
		}
		break;
	default:
		break;
	}

}

const void AHexagonalTile::NotifyNeighbors(ETileInteractionMessage Message, const ETileInteractionAction NotifyPattern, const UETileType HoveredTileType, const int Distance, const ETileInteractionFeedback Feedback, const FLinearColor FeedbackColor)
{
	if (Distance == 0)
	{
		return;
	}
	TSet<int> VisitedNeighbors;
	VisitedNeighbors.Add(TileIndex);
	int RemainingDistance{ Distance - 1 };
	if (IsValid(Neighbors.North))
	{
		Neighbors.North->HandleMessage(Message, NotifyPattern, HoveredTileType, VisitedNeighbors, UEHexNeighborDirection::North, Feedback, FeedbackColor, RemainingDistance);
	}
	if (IsValid(Neighbors.NorthEast))
	{
		Neighbors.NorthEast->HandleMessage(Message, NotifyPattern, HoveredTileType, VisitedNeighbors, UEHexNeighborDirection::NorthEast, Feedback, FeedbackColor, RemainingDistance);
	}
	if (IsValid(Neighbors.SouthEast))
	{
		Neighbors.SouthEast->HandleMessage(Message, NotifyPattern, HoveredTileType, VisitedNeighbors, UEHexNeighborDirection::SouthEast, Feedback, FeedbackColor, RemainingDistance);
	}
	if (IsValid(Neighbors.South))
	{
		Neighbors.South->HandleMessage(Message, NotifyPattern, HoveredTileType, VisitedNeighbors, UEHexNeighborDirection::South, Feedback, FeedbackColor, RemainingDistance);
	}
	if (IsValid(Neighbors.SouthWest))
	{
		Neighbors.SouthWest->HandleMessage(Message, NotifyPattern, HoveredTileType, VisitedNeighbors, UEHexNeighborDirection::SouthWest, Feedback, FeedbackColor, RemainingDistance);
	}
	if (IsValid(Neighbors.NorthWest))
	{
		Neighbors.NorthWest->HandleMessage(Message, NotifyPattern, HoveredTileType, VisitedNeighbors, UEHexNeighborDirection::NorthWest, Feedback, FeedbackColor, RemainingDistance);
	}
}

void AHexagonalTile::HandleTileCursorOverBegin(const ETileInteractionAction NotifyPattern, const ETileInteractionFeedback Feedback, const FLinearColor FeedbackColor, const int NotifyDistance)
{
	NotifyNeighbors(ETileInteractionMessage::BeginCursorOver, NotifyPattern, TileType, NotifyDistance, Feedback, FeedbackColor);
}

void AHexagonalTile::HandleTileCursorOverEnd(const ETileInteractionAction NotifyPattern, const int NotifyDistance)
{
	NotifyNeighbors(ETileInteractionMessage::EndCursorOver, NotifyPattern, TileType, NotifyDistance);
}
