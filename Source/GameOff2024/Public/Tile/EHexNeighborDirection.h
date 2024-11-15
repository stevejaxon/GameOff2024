#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class UEHexNeighborDirection : uint8
{
	North UMETA(DisplayName = "North"),
	NorthEast UMETA(DisplayName = "NorthEast"),
	SouthEast UMETA(DisplayName = "SouthEast"),
	South UMETA(DisplayName = "South"),
	SouthWest UMETA(DisplayName = "SouthWest"),
	NorthWest UMETA(DisplayName = "NorthWest"),
};
