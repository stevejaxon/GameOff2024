#include "GameModes/MainGameModeBase.h"
#include "GameModes/MainGameInstance.h"
#include "Procedural/TileGridConfiguration.h"

void AMainGameModeBase::InitGameState()
{
	Super::InitGameState();

	UMainGameInstance* GameInstanceRef{ GetGameInstance<UMainGameInstance>() };
	if (!IsValid(GameInstanceRef))
	{
		UE_LOG(LogTemp, Warning, TEXT("The Game Mode could not be initialized because the Game Instance did not match the expected type."));
		return;
	}
	FTileGridConfiguration LevelConfig{ GameInstanceRef->LevelConfig };

	MainGameStateRef = Cast<AMainGameStateBase>(GameState);
	if (IsValid(MainGameStateRef))
	{
		MainGameStateRef->Initialize(MoveTemp(LevelConfig));
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

FTileGridConfiguration* AMainGameModeBase::GridSpawningConfig()
{
	return &MainGameStateRef->LevelConfig;
}
