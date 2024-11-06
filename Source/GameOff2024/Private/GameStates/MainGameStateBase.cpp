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
		TArray<int> NeighborIndices = TileRef->AdjacentTileIndices(TotalTiles, GridWidth);
		TArray<ATileBase*> TilesNeighbors;
		TilesNeighbors.Init(nullptr, TileRef->NumberOfNeighbors());
		for (const int NeighborIndex : NeighborIndices)
		{
			if (NeighborIndex >= 0)
			{
				ATileBase* NeighborRef = GridStateRefs[NeighborIndex];
			}
		}
		TileRef->PopulateNeighbors(TilesNeighbors);
	}
}
