#include "GameStates/MainGameStateBase.h"

void AMainGameStateBase::Initialize(int Width, int Height)
{
	GridWidth = Width;
	GridHeight = Height;
	TotalTiles = Width * Height;
	GridStateRefs.SetNum(TotalTiles);
	FTileContents DefaultTile{ UETileType::Grass };
	GridContents.Init(DefaultTile, TotalTiles);
}

void AMainGameStateBase::AddToGridState(ATileBase&& Tile, int Index)
{
	if (Index > GridStateRefs.Num())
	{
		return;
	}
	GridStateRefs.Insert(&Tile, Index);
}

void AMainGameStateBase::PopulateTilesNeighbors()
{
	for (ATileBase* TileRef : GridStateRefs)
	{
		if (!IsValid(TileRef))
		{
			continue;
		}

		TArray<int> NeighborIndices = TileRef->AdjacentTileIndices(TotalTiles, GridWidth);

		TArray<ATileBase*> TilesNeighbors;
		TilesNeighbors.Init(nullptr, TileRef->NumberOfNeighbors());
		for (int i = 0; i < TileRef->NumberOfNeighbors(); i++)
		{
			const int NeighborIndex{ NeighborIndices[i] };
			if (NeighborIndex >= 0)
			{
				ATileBase* NeighborRef = GridStateRefs[NeighborIndex];
				if (IsValid(NeighborRef))
				{
					TilesNeighbors[i] = NeighborRef;
				}
			}
		}
		TileRef->PopulateNeighbors(TilesNeighbors);
	}
}
