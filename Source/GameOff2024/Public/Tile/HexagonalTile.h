#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "HexagonalTile.generated.h"

UCLASS()
class GAMEOFF2024_API AHexagonalTile : public AActor
{
	GENERATED_BODY()
	
public:	
	AHexagonalTile();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticMeshComp;
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
