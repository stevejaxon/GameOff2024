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

		UE_LOG(LogTemp, Warning, TEXT("BEGIN FIND ADJACENT NEIGHBORS FOR TILE WITH INDEX %d"), TileRef->TileIndex);

		TArray<int> NeighborIndices = TileRef->AdjacentTileIndices(TotalTiles, GridWidth);

		UE_LOG(LogTemp, Warning, TEXT("THE TILE WITH INDEX %d HAS THE FOLLOWING NEIGHBORING TILE INDICES: %d, %d, %d, %d, %d, %d"), TileRef->TileIndex, NeighborIndices[0], NeighborIndices[1], NeighborIndices[2], NeighborIndices[3] , NeighborIndices[4], NeighborIndices[5]);

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
					UE_LOG(LogTemp, Warning, TEXT("THE TILE WITH INDEX %d HAS A VALID REF TO THE NEIGHBOR %d. NEIGHBORS TILE INDEX IS %d."), TileRef->TileIndex, NeighborIndex, NeighborRef->TileIndex);
					TilesNeighbors[i] = NeighborRef;
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("THE TILE WITH INDEX %d DOES NOT HAVE A VALID REF TO THE NEIGHBOR %d"), TileRef->TileIndex, NeighborIndex);
				}
			}
		}
		TileRef->PopulateNeighbors(TilesNeighbors);
	}
}
