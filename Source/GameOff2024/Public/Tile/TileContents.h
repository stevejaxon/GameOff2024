#pragma once

#include "CoreMinimal.h"
#include "Tile/ETileType.h"
#include "Tile/ETileModifier.h"

#include "TileContents.generated.h"
/**
 * 
 */
USTRUCT(BlueprintType)
struct GAMEOFF2024_API FTileContents
{
public:
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite) UETileType TileBase;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<UETileModifier> TileModifiers;
};
