#include "GameModes/MainGameModeBase.h"

void AMainGameModeBase::InitGameState()
{
	Super::InitGameState();

	MainGameStateRef = Cast<AMainGameStateBase>(GameState);
	MainGameStateRef->Initialize(8, 6);
}

void AMainGameModeBase::StoreTileRef(ATileBase&& Tile, int Index)
{
	MainGameStateRef->AddToGridState(MoveTemp(Tile), Index);
}

void AMainGameModeBase::TileSpawningCompleted()
{
	MainGameStateRef->PopulateTilesNeighbors();
}
