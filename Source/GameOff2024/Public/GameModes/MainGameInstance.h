#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Procedural/TileGridConfiguration.h"

#include "MainGameInstance.generated.h"

const FName MainLevelName("LV_Main");
const FName MainMenuName("LV_Main_Menu");
const FName IntroductionLevelName("LV_Introduction");
const FName EndLevelName("LV_End");
const FName TutorialLevelName("LV_Tutorial");

/**
 * 
 */
UCLASS()
class GAMEOFF2024_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()

	int CurrentLevel{ 0 };
	int CaloriesCollected{ 0 };
	int MaxCalories{ 1000 };
	TArray<FName> Levels{ MainMenuName, IntroductionLevelName, TutorialLevelName, TutorialLevelName, TutorialLevelName, MainLevelName, MainLevelName, MainLevelName, EndLevelName };

	bool LoadNamedLevelConfig(FName LevelName);
public:
	// Override `UGameInstance::Init` to initialize our custom Game Instance class
	virtual void Init();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) FTileGridConfiguration LevelConfig;

	/*
	* Deprecated
	*/
	UFUNCTION(BlueprintCallable) void LoadNextLevel(FName LevelName);

	UFUNCTION(BlueprintCallable) void NextLevel();

	UFUNCTION(BlueprintCallable) int GetCaloriesCollected();
	UFUNCTION(BlueprintCallable) int GetMaxPossibleCalories();
};
