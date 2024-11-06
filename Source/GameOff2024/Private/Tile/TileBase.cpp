#include "Tile/TileBase.h"

ATileBase::ATileBase()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	StaticMeshComp->SetupAttachment(RootComponent);
}

void ATileBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

