#include "GameModes/MainGameModeBase.h"

void AMainGameModeBase::InitGameState()
{
	Super::InitGameState();

	MainGameStateRef = Cast<AMainGameStateBase>(GameState);
	if (IsValid(MainGameStateRef))
	{
		MainGameStateRef->Initialize(8, 6);
	}
}

void AMainGameModeBase::StoreTileRef(ATileBase&& Tile, int Index)
{
	MainGameStateRef->AddToGridState(MoveTemp(Tile), Index);
}

void AMainGameModeBase::TileSpawningCompleted()
{
	MainGameStateRef->PopulateTilesNeighbors();
}

FTileGridConfiguration AMainGameModeBase::GridSpawningConfig()
{
	FTileGridConfiguration Config;
	Config.GridWidth = MainGameStateRef->GridWidth;
	Config.GridHeight = MainGameStateRef->GridHeight;
	Config.GridContents = &MainGameStateRef->GridContents;
	return Config;
}
