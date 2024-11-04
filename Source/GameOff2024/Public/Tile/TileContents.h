#pragma once

#include "CoreMinimal.h"
#include "Tile/ETileType.h"
#include "Tile/ETileModifier.h"

/**
 * 
 */
struct GAMEOFF2024_API TileContents
{
public:
	const UETileType TileBase;
	const TArray<UETileModifier> TileModifiers;
	
	TileContents(UETileType _TileBase, TArray<UETileModifier> _TileModifiers) : TileBase(_TileBase), TileModifiers(_TileModifiers) {};
	~TileContents();
};
