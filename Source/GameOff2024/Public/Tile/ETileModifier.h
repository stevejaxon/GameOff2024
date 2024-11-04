#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class UETileModifier : uint8
{
	None UMETA(DisplayName = "None"),
	Tree UMETA(DisplayName = "Tree"),
	House UMETA(DisplayName = "House")
};