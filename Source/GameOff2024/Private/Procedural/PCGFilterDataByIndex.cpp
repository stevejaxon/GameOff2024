#include "Procedural/PCGFilterDataByIndex.h"
#include "PCGContext.h"
#include "Data/PCGPointData.h"
#include "Helpers/PCGAsync.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(PCGFilterDataByIndex)

#define LOCTEXT_NAMESPACE "PCGFilterDataByIndexElement"

#if WITH_EDITOR
FName UPCGFilterDataByIndexSettings::GetDefaultNodeName() const
{
	return FName(TEXT("FilterDataByProvidedIndex"));
}

FText UPCGFilterDataByIndexSettings::GetDefaultNodeTitle() const
{
	return LOCTEXT("NodeTitle", "Filter PCG Data By Index");
}

FText UPCGFilterDataByIndexSettings::GetNodeTooltipText() const
{
	return LOCTEXT("FilterDataByProvidedIndexTooltip", "Filters data in the collection according to user provided index.");
}
#endif

FString UPCGFilterDataByIndexSettings::GetAdditionalTitleInformation() const
{
	return FString::Printf(TEXT("Index: %d"), IncludeDataUpToIndex);
}

FPCGElementPtr UPCGFilterDataByIndexSettings::CreateElement() const
{
	return MakeShared<UPCGFilterDataByIndexElement>();
}

#undef LOCTEXT_NAMESPACE

bool UPCGFilterDataByIndexElement::ExecuteInternal(FPCGContext* Context) const
{
	TRACE_CPUPROFILER_EVENT_SCOPE(UPCGFilterDataByIndexElement::ExecuteInternal);

	const UPCGFilterDataByIndexSettings* Settings = Context->GetInputSettings<UPCGFilterDataByIndexSettings>();
	check(Settings);

	const TArray<FPCGTaggedData> Inputs = Context->InputData.GetInputs();

	if (Inputs.IsEmpty())
	{
		return true;
	}

	TArray<FPCGTaggedData>& Outputs = Context->OutputData.TaggedData;

	int FilterIndexLimit{ Settings->IncludeDataUpToIndex };
	for (const FPCGTaggedData& Input : Inputs)
	{
		FPCGTaggedData& Output = Outputs.Add_GetRef(Input);

		if (!Input.Data || Cast<UPCGSpatialData>(Input.Data) == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("UPCGFilterDataByIndexElement: Invalid input data"));
			continue;
		}

		const UPCGPointData* OriginalData = Cast<UPCGSpatialData>(Input.Data)->ToPointData(Context);

		if (!OriginalData)
		{
			UE_LOG(LogTemp, Error, TEXT("UPCGFilterDataByIndexElement: Unable to get point data from input"));
			continue;
		}

		const TArray<FPCGPoint>& Points = OriginalData->GetPoints();

		UPCGPointData* FilteredData = NewObject<UPCGPointData>();
		FilteredData->InitializeFromData(OriginalData);
		TArray<FPCGPoint>& FilteredPoints = FilteredData->GetMutablePoints();

		Output.Data = FilteredData;

		FPCGAsync::AsyncPointProcessing(Context, Points.Num(), FilteredPoints, [&Points, FilterIndexLimit](int32 Index, FPCGPoint& OutPoint)
			{
				if (Index >= FilterIndexLimit)
				{
					return false;
				}

				const FPCGPoint& Point = Points[Index];
					OutPoint = Point;
					return true;
			});
	}

	return true;
}
