#pragma once

#include "CoreMinimal.h"
#include "PCGSettings.h"
#include "Elements/PCGFilterDataBase.h"

#include "PCGFilterDataByIndex.generated.h"

/**
 * Filters a data collection based on a user defined index value.
 * Based on UE's UPCGDensityFilterSettings and UPCGFilterByIndexSettings.
 */
UCLASS(MinimalAPI, BlueprintType, ClassGroup = (Procedural))
class UPCGFilterDataByIndexSettings : public UPCGFilterDataBaseSettings
{
	GENERATED_BODY()

public:
	//~Begin UPCGSettings interface
#if WITH_EDITOR
	virtual FName GetDefaultNodeName() const override;
	virtual FText GetDefaultNodeTitle() const override;
	virtual FText GetNodeTooltipText() const override;
	virtual EPCGSettingsType GetType() const override { return EPCGSettingsType::Filter; }
#endif

	virtual FString GetAdditionalTitleInformation() const override;

protected:
#if WITH_EDITOR
	virtual TArray<FPCGPinProperties> InputPinProperties() const override { return Super::DefaultPointInputPinProperties(); }
	virtual TArray<FPCGPinProperties> OutputPinProperties() const override { return Super::DefaultPointOutputPinProperties(); }
#endif
	virtual FPCGElementPtr CreateElement() const override;
	//~End UPCGSettings interface

public:
	/**
	 * Filter the input dataset up until the specified Index. Exclusive i.e. [0,X).
	 * For example, on an array of size 10: '5' will include indices: 0,1,2,3,4,5. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Settings, meta = (PCG_Overridable));
	int IncludeDataUpToIndex;
};

class UPCGFilterDataByIndexElement : public IPCGElement
{
protected:
	virtual bool ExecuteInternal(FPCGContext* Context) const override;
};