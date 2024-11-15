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

UENUM(BlueprintType)
enum class ETileInteractionAction : uint8
{
	NotifyNeighborsRadially UMETA(DisplayName = "Notify All Radially Adjacent Neighbors Action"),
	NotifyNeighborsDirectionally UMETA(DisplayName = "Notify All Directionally Adjacent Neighbors Action"),
};

UENUM(BlueprintType)
enum class ETileInteractionFeedback : uint8
{
	None UMETA(DisplayName = "No feedback"),
	Positive UMETA(DisplayName = "Positive interaction feedback"),
	Negative UMETA(DisplayName = "Negative interaction feedback"),
};