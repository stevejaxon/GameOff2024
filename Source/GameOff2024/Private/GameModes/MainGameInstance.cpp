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

const TMap<FName, FTileGridConfiguration> LevelConfigMap{
	{MainMenuName, FTileGridConfiguration{5, 5, {4}, TArray<FTileContents>{
		EmptyWoodlandsTile, EmptyWoodlandsTile, EmptyCityTile, EmptyGrasslandsTile, EmptyGrasslandsTile,
		EmptyGrasslandsTile, EmptyWaterTile, EmptyWaterTile, EmptyWaterTile, EmptyGrasslandsTile,
		EmptyWoodlandsTile, EmptyWoodlandsTile, EmptySuburbTile, EmptyWoodlandsTile, EmptyWoodlandsTile,
		EmptyWoodlandsTile, EmptyWoodlandsTile, EmptyWaterTile, EmptyWaterTile, EmptyGrasslandsTile,
		EmptyCityTile, EmptyCityTile, EmptyCityTile, EmptyWaterTile, EmptyGrasslandsTile,
	}}},
	{IntroductionLevelName, FTileGridConfiguration{1, 1, {0}, TArray<FTileContents>{}}},
	{FName("LV_Tutorial_1"), FTileGridConfiguration{3, 2, {0,1,2,3,4,5}, TArray<FTileContents>{EmptyWoodlandsTile, EmptyWoodlandsTile, EmptyWoodlandsTile, EmptyWoodlandsTile, EmptyWoodlandsTile, EmptyWoodlandsTile}}},
	{FName("LV_Tutorial_2"), FTileGridConfiguration{3, 2, {1,3,5}, TArray<FTileContents>{EmptyWaterTile, EmptyWoodlandsTile, EmptyWaterTile, EmptyWoodlandsTile, EmptyWoodlandsTile, EmptyWoodlandsTile}}},
	{FName("LV_Tutorial_3"), FTileGridConfiguration{3, 3, {0}, TArray<FTileContents>{EmptyWoodlandsTile, EmptyWaterTile, EmptyWaterTile, EmptyMountainTile, EmptyGrasslandsTile, EmptyGrasslandsTile, EmptyGrasslandsTile, EmptyCityTile, EmptyWaterTile}}},
};

void UMainGameInstance::Init()
{
	// Load the main menu's procedural spawning config by default, so that we have config loaded when the game starts.
	LoadNamedLevelConfig(MainMenuName);
}

void UMainGameInstance::LoadNamedLevelConfig(FName LevelName)
{
	// Fallback to loading the main menu if an invalid level is trying to be loaded
	if (!LevelConfigMap.Contains(LevelName))
	{
		LevelConfig = LevelConfigMap[MainMenuName];
		return;
	}
	LevelConfig = LevelConfigMap[LevelName];
}

void UMainGameInstance::LoadNextLevel(FName LevelName)
{
	LoadNamedLevelConfig(LevelName);
	UGameplayStatics::OpenLevel(this, LevelName, true);
}

void UMainGameInstance::NextLevel()
{
	int NextLevel{ CurrentLevel + 1 };
	if (NextLevel >= Levels.Num())
	{
		UE_LOG(LogTemp, Warning, TEXT("Can not load the level with number %d, it does not exist"), NextLevel);
		return;
	}
	FName NextLevelName{ Levels[NextLevel] };
	if (NextLevelName.IsEqual(MainLevelName))
	{
		// The main level "map" is designed to be able to procedurally generate levels, but in the short term hardcode hand-design level patterns (similar to the tutorial levels) to "make it work".
		const FString NewLevelName{ FString::Printf(TEXT("%s_%d"), *MainLevelName.ToString(), NextLevel)};
		NextLevelName = FName(*NewLevelName);
	}
	LoadNamedLevelConfig(NextLevelName);
	CurrentLevel = NextLevel;
	UGameplayStatics::OpenLevel(this, NextLevelName, true);
}
