#include "Procedural/HexagonalTileSpawner.h"
#include "GameModes/MainGameModeBase.h"
#include "Procedural/TileGridConfiguration.h"

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

void AHexagonalTileSpawner::SpawnGrid()
{
	UWorld* WorldRef{ GetWorld() };
	AMainGameModeBase* GameModeBaseRef{ Cast<AMainGameModeBase>(WorldRef->GetAuthGameMode()) };
	FTileGridConfiguration* SpawningConfig{ GameModeBaseRef->GridSpawningConfig() };
	if (SpawningConfig == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Unable to spawn the grid because the configuration is missing."));
		return;
	}
	TArray<FTileContents> Tiles{ SpawningConfig->GridContents };

	int TileIndex = 0;

	for (int Row = 0; Row < SpawningConfig->GridHeight; Row++)
	{
		float RowsVerticalOffset{TileHeight * Row};

		for (int Column = 0; Column < SpawningConfig->GridWidth; Column++)
		{
			float HorizontalOffset{(float(StartLocation.Y) + BaseHorizontalOffset) * Column};
			float VerticalOffset = Column % 2 == 0 ? RowsVerticalOffset : RowsVerticalOffset + (TileHeight / 2);
			const FVector SpawnLocation(VerticalOffset, HorizontalOffset, 0);

			FTileContents Contents{ Tiles[TileIndex] };
			UClass* TileClass = TileClassRefMap[Contents.TileBase];
			AActor* ActorRef{ WorldRef->SpawnActor(TileClass, &SpawnLocation, &SpawnRotation) };
			AHexagonalTile* HexTileRef = Cast<AHexagonalTile>(ActorRef);
			if (IsValid(HexTileRef))
			{
				HexTileRef->TileIndex = TileIndex;
				HexTileRef->TileType = Contents.TileBase;
				GameModeBaseRef->StoreTileRef(MoveTemp(*HexTileRef), TileIndex);
			}

			TileIndex++;
		}
	}

	GameModeBaseRef->TileSpawningCompleted();
}

