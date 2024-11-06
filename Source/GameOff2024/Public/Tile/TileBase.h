#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileBase.generated.h"

UCLASS()
class GAMEOFF2024_API ATileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ATileBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int TileIndex;
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual const int NumberOfNeighbors() { return 0; };
	virtual void NotifyNeighbors() {};
	virtual const TArray<int> AdjacentTileIndices(const int TotalTiles, const int GridWidth) { return TArray<int>(); }
	virtual void PopulateNeighbors(const TArray<ATileBase*>& NeighborRefs) {};
};
