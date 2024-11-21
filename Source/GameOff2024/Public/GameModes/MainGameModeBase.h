#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameStates/MainGameStateBase.h"
#include "Procedural/TileGridConfiguration.h"

#include "MainGameModeBase.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRevealTileContentsDispatcher, int, SelectedTileIndex);

/**
 * 
 */
UCLASS()
class GAMEOFF2024_API AMainGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private:
	AMainGameStateBase* MainGameStateRef;

public:
	// Override `AGameModeBase::InitGameState` to initialize our custom Game State class
	void InitGameState() override;

	void StoreTileRef(ATileBase&& Tile, int Index);
	void TileSpawningCompleted();
	FTileGridConfiguration* GridSpawningConfig();

	UFUNCTION(BlueprintCallable) const bool IsGoalLocation(const int SelectedTileIndex);

	UFUNCTION(BlueprintImplementableEvent) void OnLoadNextLevel();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable) void TileSelected(const int SelectedTileIndex);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable) void SelectedTilesContentsRevealed(const int SelectedTileIndex);

	UPROPERTY(BlueprintAssignable, BlueprintCallable) FRevealTileContentsDispatcher OnRevealTileContents;
};
