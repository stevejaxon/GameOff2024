#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Procedural/TileGridConfiguration.h"

#include "MainGameInstance.generated.h"

const FName MainLevelName("LV_Main_Menu");
const FName MainMenuName("LV_Main_Menu");

/**
 * 
 */
UCLASS()
class GAMEOFF2024_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()

	int CurrentLevel{ 0 };
	TArray<FName> Levels{ MainMenuName, "LV_Tutorial_1",  "LV_Tutorial_2", "LV_Tutorial_3", MainLevelName, MainLevelName, MainLevelName};

	void LoadNamedLevelConfig(FName LevelName);
public:
	// Override `UGameInstance::Init` to initialize our custom Game Instance class
	virtual void Init();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) FTileGridConfiguration LevelConfig;

	/*
	* Deprecated
	*/
	UFUNCTION(BlueprintCallable) void LoadNextLevel(FName LevelName);

	UFUNCTION(BlueprintCallable) void NextLevel();
};
