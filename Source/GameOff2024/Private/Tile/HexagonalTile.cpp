#include "Tile/HexagonalTile.h"

AHexagonalTile::AHexagonalTile()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	StaticMeshComp->SetupAttachment(RootComponent);
}

void AHexagonalTile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHexagonalTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

