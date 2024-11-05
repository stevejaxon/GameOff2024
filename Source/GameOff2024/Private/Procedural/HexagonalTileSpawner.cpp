#include "Procedural/HexagonalTileSpawner.h"

AHexagonalTileSpawner::AHexagonalTileSpawner()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AHexagonalTileSpawner::SetTileLength(float Amount)
{
	if (Amount <= 0.0f)
	{
		return;
	}
	TileLength = Amount;
	TileWidth = Amount * 2;
	TileHeight = FMath::Sqrt(3.0f) * Amount;
	BaseVerticalOffset = TileHeight / 2;
	BaseHorizontalOffset = 0.75f * TileWidth;
}

void AHexagonalTileSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHexagonalTileSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHexagonalTileSpawner::SpawnGrid(const int Rows, const int Columns, const TArray<FTileContents> Tiles)
{
	if (Rows <= 0 || Columns <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("The grid of hexagonal tiles was not spawned due to incorrect parameters. Rows %d, Columns %d."), Rows, Columns);
		return;
	}

	int TotalTiles{ Rows * Columns };
	if (Tiles.Num() != TotalTiles)
	{
		UE_LOG(LogTemp, Warning, TEXT("The grid of hexagonal tiles was not spawned due to incorrect parameters. Expected %d tiles, but got %d."), TotalTiles, Tiles.Num());
		return;
	}

	UWorld* WorldRef{ GetWorld() };
	int TileIndex = 0;

	for (int Row = 0; Row < Rows; Row++)
	{
		FTileContents Contents{ Tiles[TileIndex] };
		UClass* TileClass = TileClassRefMap[Contents.TileBase];
		float RowsVerticalOffset{TileHeight / 2};

		UE_LOG(LogTemp, Warning, TEXT("ROW: %d"), Row);

		for (int Column = 0; Column < Columns; Column++)
		{
			float HorizontalOffset{(float(StartLocation.Y) + BaseHorizontalOffset) * Column};
			float VerticalOffset = Column % 2 == 0 ? 0.0f : RowsVerticalOffset;
			const FVector SpawnLocation(VerticalOffset, HorizontalOffset, 0);

			UE_LOG(LogTemp, Warning, TEXT("COLUMN: %d. HorizOffset: %f. VertOffset: %f."), Column, HorizontalOffset, VerticalOffset);


			WorldRef->SpawnActor(TileClass, &SpawnLocation, &SpawnRotation);

			TileIndex++;
		}
	}
}

