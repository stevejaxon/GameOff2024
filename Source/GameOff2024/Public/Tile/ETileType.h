#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class UETileType : uint8
{
	None UMETA(DisplayName = "None"),
	Grass UMETA(DisplayName = "Grass"),
	Stone UMETA(DisplayName = "Stone"),
	Dirt UMETA(DisplayName = "Dirt"),
	Water UMETA(DisplayName = "Water"),
	Road UMETA(DisplayName = "Road"),
	River UMETA(DisplayName = "River")
};