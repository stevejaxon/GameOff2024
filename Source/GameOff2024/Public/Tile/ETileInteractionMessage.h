#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class ETileInteractionMessage : uint8
{
	BeginCursorOver UMETA(DisplayName = "BeginCursorOver Event"),
	EndCursorOver UMETA(DisplayName = "EndCursorOver Event"),
	RevealContents UMETA(DisplayName = "Reveal Tile's Contents"),
	Selected UMETA(DisplayName = "Tile Selected Event"),
};
