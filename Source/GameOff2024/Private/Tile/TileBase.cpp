#include "Tile/TileBase.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"

ATileBase::ATileBase()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	StaticMeshComp->SetupAttachment(RootComponent);
	TileHighlightedWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("TileHighlightedWidgetComp"));
	TileHighlightedWidgetComp->SetupAttachment(RootComponent);
	TileHighlightedFeedbackWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("TileHighlightedFeedbackWidgetComp"));
	TileHighlightedFeedbackWidgetComp->SetupAttachment(RootComponent);
	TileSelectedWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("TileSelectedWidgetComp"));
	TileSelectedWidgetComp->SetupAttachment(RootComponent);
}

void ATileBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATileBase::LoadPCGObjectRefs()
{
	if (PCGStaticMeshComponents.Num() != 0)
	{
		return;
	}

	PCGStaticMeshComponents = this->GetComponentsByTag(UHierarchicalInstancedStaticMeshComponent::StaticClass(), FName("PCG"));
}

void ATileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATileBase::HandlePGCGenerationCompleted()
{
	LoadPCGObjectRefs();
}

void ATileBase::HidePCGComponents()
{
	for (UActorComponent* CompRef : PCGStaticMeshComponents)
	{
		UHierarchicalInstancedStaticMeshComponent* HISMCRef{ Cast<UHierarchicalInstancedStaticMeshComponent>(CompRef) };
		if (IsValid(HISMCRef))
		{
			HISMCRef->SetVisibility(false, true);
		}
	}
}

void ATileBase::ShowPCGComponents()
{
	for (UActorComponent* CompRef : PCGStaticMeshComponents)
	{
		UHierarchicalInstancedStaticMeshComponent* HISMCRef{ Cast<UHierarchicalInstancedStaticMeshComponent>(CompRef) };
		if (IsValid(HISMCRef))
		{
			HISMCRef->SetVisibility(true, true);
		}
	}
}

void ATileBase::DeletePCGComponentsInDigArea(const double Radius)
{
	FVector TileCenter{ RootComponent->GetComponentLocation() };
	TArray<UActorComponent*> PCGComponentsToDelete;

	for (UActorComponent* CompRef : PCGStaticMeshComponents)
	{
		UHierarchicalInstancedStaticMeshComponent* HISMCRef{ Cast<UHierarchicalInstancedStaticMeshComponent>(CompRef) };
		if (IsValid(HISMCRef))
		{
			for (const int32 InstanceID : HISMCRef->GetInstancesOverlappingSphere(TileCenter, Radius))
			{
				HISMCRef->RemoveInstance(InstanceID);
			}
		}
	}
}
