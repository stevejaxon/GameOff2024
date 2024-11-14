#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "Tile/ETileInteractionMessage.h"

#include "TileBase.generated.h"

UCLASS()
class GAMEOFF2024_API ATileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ATileBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWidgetComponent* TileHighlightedWidgetComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWidgetComponent* TileHighlightedFeedbackWidgetComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWidgetComponent* TileSelectedWidgetComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int TileIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<UActorComponent*> PCGStaticMeshComponents;
protected:
	virtual void BeginPlay() override;

	virtual void NotifyNeighbors(ETileInteractionMessage Message, int Distance) {};
	virtual void HandleMessage(ETileInteractionMessage Message) {};

	void LoadPCGObjectRefs();
public:	
	virtual void Tick(float DeltaTime) override;

	virtual const int NumberOfNeighbors() { return 0; };
	virtual const TArray<int> AdjacentTileIndices(const int TotalTiles, const int GridWidth) { return TArray<int>(); }
	virtual void PopulateNeighbors(const TArray<ATileBase*>& NeighborRefs) {};

	UFUNCTION(BlueprintCallable) void HandlePGCGenerationCompleted();
	UFUNCTION(BlueprintCallable) void HidePCGComponents();
	UFUNCTION(BlueprintCallable) void ShowPCGComponents();
	UFUNCTION(BlueprintCallable) virtual void HandleTileCursorOverBegin() {};
	UFUNCTION(BlueprintCallable) virtual void HandleTileCursorOverEnd() {};

	UFUNCTION(BlueprintImplementableEvent) void OnHighlightTileStart();
	UFUNCTION(BlueprintImplementableEvent) void OnHighlightTileEnd();
};
