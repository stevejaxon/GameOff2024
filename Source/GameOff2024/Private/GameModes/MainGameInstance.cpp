#include "GameModes/MainGameInstance.h"
#include "Tile/TileContents.h"
#include "Tile/ETileType.h"
#include "Kismet/GameplayStatics.h"

const FTileContents EmptyWoodlandsTile{UETileType::Woodland};
const FTileContents EmptyGrasslandsTile{UETileType::Grassland};
const FTileContents EmptyWaterTile{UETileType::Water};
const FTileContents EmptyMountainTile{ UETileType::Mountain };
const FTileContents EmptyCityTile{ UETileType::City };
const FTileContents EmptySuburbTile{ UETileType::Suburb };
const FTileContents EmptySavannaTile{ UETileType::Savanna };

const FName MainMenuName("LV_Main_Menu");

const TMap<FName, FTileGridConfiguration> LevelConfigMap{
	{MainMenuName, FTileGridConfiguration{3, 3, 1, {4}, TArray<FTileContents>{EmptyWoodlandsTile, EmptyWoodlandsTile, EmptyCityTile, EmptyGrasslandsTile, EmptyGrasslandsTile, EmptyGrasslandsTile, EmptyWaterTile, EmptyWaterTile, EmptyWaterTile}}},
	{FName("LV_Tutorial_1"), FTileGridConfiguration{3, 3, 1, {4}, TArray<FTileContents>{EmptyWoodlandsTile, EmptyWoodlandsTile, EmptyCityTile, EmptyGrasslandsTile, EmptyGrasslandsTile, EmptyGrasslandsTile, EmptyWaterTile, EmptyWaterTile, EmptyWaterTile}}},
	{FName("LV_Tutorial_2"), FTileGridConfiguration{3, 3, 2, {1,3}, TArray<FTileContents>{EmptyWoodlandsTile, EmptyWoodlandsTile, EmptyCityTile, EmptyGrasslandsTile, EmptyGrasslandsTile, EmptyGrasslandsTile, EmptyWaterTile, EmptyWaterTile, EmptyWaterTile}}},
};

void UMainGameInstance::Init()
{
	// Load the main menu's procedural spawning config by default, so that we have config loaded when the game starts.
	LoadNamedLevelConfig(MainMenuName);
}

void UMainGameInstance::LoadNamedLevelConfig(FName LevelName)
{
	LevelConfig = LevelConfigMap[LevelName];
}

void UMainGameInstance::LoadNextLevel(FName LevelName)
{
	LoadNamedLevelConfig(LevelName);
	UGameplayStatics::OpenLevel(this, LevelName, true);
}
