#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "math.h"
#include "Procedural/TileSpawner.h"
#include "Tile/ETileType.h"
#include "Tile/HexagonalTile.h"

#include "HexagonalTileSpawner.generated.h"

UCLASS()
class GAMEOFF2024_API AHexagonalTileSpawner : public AActor, public ITileSpawner
{
	GENERATED_BODY()
	
	float TileLength{ 1.0f };
	float TileWidth{ 2.0f };
	float TileHeight{ FMath::Sqrt(3.0f) };
	float BaseHorizontalOffset{ 0.75f * TileWidth };
	float BaseVerticalOffset{ TileHeight / 2 };

public:	
	AHexagonalTileSpawner();

	UPROPERTY(EditAnywhere, BlueprintReadWrite) 
	TMap<UETileType, UClass*> TileClassRefMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector StartLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator SpawnRotation;

	UFUNCTION(BlueprintCallable) void SetTileLength(float Amount);
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SpawnGrid(int Rows, int Columns, TArray<TileContents> Tiles) override;
};
