#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Procedural/TileGridConfiguration.h"

#include "MainGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class GAMEOFF2024_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()

	void LoadNamedLevelConfig(FName LevelName);
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FTileGridConfiguration LevelConfig;

	UFUNCTION(BlueprintCallable) void LoadNextLevel(FName LevelName);
};
