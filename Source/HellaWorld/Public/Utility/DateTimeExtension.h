// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DateTimeExtension.generated.h"


UENUM(Meta = (Bitflags), BlueprintType)
enum class EDateTimeRelevancy : uint8
{
	Minute,
	Hour,
	Day,
	DayOfWeek,
	Month,
	Year
};

UENUM(BlueprintType)
enum class EDayOfWeekBP : uint8
{
	Monday = 0,
	Tuesday,
	Wednesday,
	Thursday,
	Friday,
	Saturday,
	Sunday
};


/**
 * 
 */
UCLASS()
class HELLAWORLD_API UDateTimeExtension : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/** Day Month Year */
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Utility", BlueprintPure)
	static int32 DateMask();

	/** Minute Hour*/
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Utility", BlueprintPure)
	static int32 TimeMask();

	/** Minute Hour Day Month Year*/
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Utility", BlueprintPure)
	static int32 DateTimeMask();


	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Utility", BlueprintPure)
	static bool CompareDateTime(const FDateTime& A, const FDateTime& B, UPARAM(meta = (Bitmask, BitmaskEnum = EDateTimeRelevancy)) int32 RelevancyFlags);

	
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Utility", BlueprintPure)
	static FDateTime CreateDayOfWeekDate(EDayOfWeekBP DayOfWeek);
	
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Utility", BlueprintPure)
	static EDayOfWeekBP GetDayOfWeek(const FDateTime& Date);

};
