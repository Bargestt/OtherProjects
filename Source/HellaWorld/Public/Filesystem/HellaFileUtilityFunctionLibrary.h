// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HellaFileUtilityFunctionLibrary.generated.h"


UENUM(BlueprintType)
enum class EOrder : uint8
{
	Order_Ascending UMETA(DisplayName="Ascending"),
	Order_Descending UMETA(DisplayName = "Descending")
};

UENUM(BlueprintType)
enum class ESortFeature : uint8
{
	Name,
};

USTRUCT(BlueprintType)
struct FFileSortParameters
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	EOrder SortOrder;

	UPROPERTY(BlueprintReadWrite)
	ESortFeature SortBy;
	
	/** Should files be separated from folders before sorting*/
	UPROPERTY(BlueprintReadWrite)
	bool SeparateFilesAndFolders;

	FFileSortParameters()
		: SortOrder(EOrder::Order_Ascending)
		, SortBy(ESortFeature::Name)
		, SeparateFilesAndFolders(true)
	{}
};



/**
 * 
 */
UCLASS()
class HELLAWORLD_API UHellaFileUtilityFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "Filesystem|Utility")
	static void SortFiles(const TArray<UFSItem*>& InFiles, TArray<UFSItem*>& OutFiles, FFileSortParameters Parameters);
	

	
};
