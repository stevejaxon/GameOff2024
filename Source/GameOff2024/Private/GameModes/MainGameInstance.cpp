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
const FTileContents EmptyDesertTile{ UETileType::Desert };

const TMap<FName, FTileGridConfiguration> LevelConfigMap{
	{MainMenuName, FTileGridConfiguration{5, 5, {4}, TArray<FTileContents>{
		EmptyWoodlandsTile, EmptyWoodlandsTile, EmptyCityTile, EmptyGrasslandsTile, EmptyGrasslandsTile,
		EmptyGrasslandsTile, EmptyWaterTile, EmptyWaterTile, EmptyWaterTile, EmptyGrasslandsTile,
		EmptyWoodlandsTile, EmptyWoodlandsTile, EmptySuburbTile, EmptyWoodlandsTile, EmptyWoodlandsTile,
		EmptyWoodlandsTile, EmptyWoodlandsTile, EmptyWaterTile, EmptyWaterTile, EmptyGrasslandsTile,
		EmptyCityTile, EmptyCityTile, EmptyCityTile, EmptyWaterTile, EmptyGrasslandsTile,
	}}},
	{IntroductionLevelName, FTileGridConfiguration{1, 1, {0}, TArray<FTileContents>{}}},
	{EndLevelName, FTileGridConfiguration{1, 1, {0}, TArray<FTileContents>{}}}
};

const TMap <int, FTileGridConfiguration> TutorialConfigMap{
	{2, FTileGridConfiguration{3, 2, {0,1,2,3,4,5}, TArray<FTileContents>{EmptyWoodlandsTile, EmptyWoodlandsTile, EmptyWoodlandsTile, EmptyWoodlandsTile, EmptyWoodlandsTile, EmptyWoodlandsTile}}},
	{3, FTileGridConfiguration{3, 2, {1,3,5}, TArray<FTileContents>{EmptyWaterTile, EmptyWoodlandsTile, EmptyWaterTile, EmptyWoodlandsTile, EmptyWoodlandsTile, EmptyWoodlandsTile}}},
	{4, FTileGridConfiguration{3, 3, {0}, TArray<FTileContents>{EmptyWoodlandsTile, EmptyWaterTile, EmptyWaterTile, EmptyMountainTile, EmptyGrasslandsTile, EmptyGrasslandsTile, EmptyGrasslandsTile, EmptyCityTile, EmptyWaterTile}}},
};

const TMap <int, FTileGridConfiguration> MainLevelConfigMap{
	{5, FTileGridConfiguration{3, 3, {2}, TArray<FTileContents>{EmptyGrasslandsTile, EmptyWoodlandsTile, EmptyGrasslandsTile, EmptyGrasslandsTile, EmptyWoodlandsTile, EmptyWaterTile, EmptyCityTile, EmptyGrasslandsTile, EmptyGrasslandsTile}}},
	{6, FTileGridConfiguration{3, 2, {1,5}, TArray<FTileContents>{EmptyMountainTile, EmptyMountainTile, EmptyWaterTile, EmptyDesertTile, EmptyDesertTile, EmptyMountainTile}}},
	{7, FTileGridConfiguration{4, 3, {0,3}, TArray<FTileContents>{EmptyMountainTile, EmptyGrasslandsTile, EmptyWaterTile, EmptyGrasslandsTile, EmptyGrasslandsTile, EmptyGrasslandsTile, EmptyWaterTile, EmptyWaterTile, EmptyGrasslandsTile, EmptyCityTile, EmptyWoodlandsTile, EmptyGrasslandsTile}}},
};

const TMap <FName, TMap <int, FTileGridConfiguration>> LevelNameToConfigMap{
	{TutorialLevelName,TutorialConfigMap},
	{MainLevelName,MainLevelConfigMap},
};

void UMainGameInstance::Init()
{
	// Load the main menu's procedural spawning config by default, so that we have config loaded when the game starts.
	LoadNamedLevelConfig(MainMenuName);
}

bool UMainGameInstance::LoadNamedLevelConfig(FName LevelName)
{
	if (LevelNameToConfigMap.Contains(LevelName))
	{
		if (LevelNameToConfigMap[LevelName].Contains(CurrentLevel))
		{
			LevelConfig = LevelNameToConfigMap[LevelName][CurrentLevel];
			return true;
		}
		UE_LOG(LogTemp, Warning, TEXT("Can not load the level with name %s and config number %d, it does not exist"), *LevelName.ToString(), CurrentLevel);
	}
	else if (LevelConfigMap.Contains(LevelName))
	{
		LevelConfig = LevelConfigMap[LevelName];
		return true;
	}
	// Fallback to loading the main menu if an invalid level is trying to be loaded
	LevelConfig = LevelConfigMap[MainMenuName];
	return false;
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
	CurrentLevel = NextLevel;
	FName NextLevelName{ Levels[NextLevel] };
	bool bConfigLoadedSuccessfully{ LoadNamedLevelConfig(NextLevelName) };

	if (!bConfigLoadedSuccessfully)
	{
		LoadNamedLevelConfig(MainMenuName);
		NextLevelName = MainMenuName;
		CurrentLevel = 0;
	}
	
	UGameplayStatics::OpenLevel(this, NextLevelName, true);
}

int UMainGameInstance::GetCaloriesCollected()
{
	return CaloriesCollected;
}

int UMainGameInstance::GetMaxPossibleCalories()
{
	return MaxCalories;
}
