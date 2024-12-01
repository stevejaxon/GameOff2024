#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class UETileType : uint8
{
	None UMETA(DisplayName = "None"),
	Grassland UMETA(DisplayName = "Grassland"),
	Woodland UMETA(DisplayName = "Woodland"),
	Savanna UMETA(DisplayName = "Savanna"),
	Mountain UMETA(DisplayName = "Mountain"),
	Water UMETA(DisplayName = "Water"),
	City UMETA(DisplayName = "City"),
	Suburb UMETA(DisplayName = "Suburb"),
	Desert UMETA(DisplayName = "Desert")
};