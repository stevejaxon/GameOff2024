#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Tile/ETileType.h"

#include "MainPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class GAMEOFF2024_API AMainPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	UETileType MostRecentlyHighlightedTileType{ UETileType::None };
};
