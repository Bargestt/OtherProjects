// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HellaUtilityFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class HELLAWORLD_API UHellaUtilityFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/** Sort string array. Does not affect input array */
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Utility")
	static void SortStringArray(const TArray<FString>& InArray, TArray<FString>& OutArray, bool Ascending = true);

	/** Sort string array. Target array will be changed */
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Utility")
	static void SortStringArrayByRef(UPARAM(ref) TArray<FString>& TargetArray, bool Ascending = true);


	/** 
	 * Adds numeric suffix '_N' to InName to make it unique in the Container
	 * If InName already has numeric suffix it will changed
	 */
	UFUNCTION(BlueprintCallable, Category="HellaWorld|Utility")
	static void MakeNameUniqueInArray(const TArray<FName>& NameArray, FName InName, FName& OutName);

	/** 
	 * Adds numeric suffix '_N' to InName to make it unique in the Container
	 * If InName already has numeric suffix it will changed
	 * Container must implement functions Num() and Contains(FName)
	 */
	template<typename T>
	static void MakeNameUniqueInContainer(const T& Container, FName InName, FName& OutName)
	{
		if (Container.Num() <= 0 || !Container.Contains(InName))
		{
			OutName = InName;
			return;
		}
		FName CurrentName = InName;
		FString NameString = CurrentName.ToString();

		FString Left, Right;
		NameString.Split(TEXT("_"), &Left, &Right, ESearchCase::IgnoreCase, ESearchDir::FromEnd);
		if (!Right.IsEmpty() && Right.IsNumeric())
		{
			NameString = Left;
		}

		int Iteration = 0;
		while (Container.Contains(CurrentName))
		{
			CurrentName = FName(*(NameString + TEXT("_") + FString::FromInt(Iteration)));
			Iteration++;
			
			if (Iteration > Container.Num()) // Lets hope this will not happen
			{
				ensureMsgf(Iteration <= Container.Num(), TEXT("'%s' -> '%s' There could not be the case where iterations will go over array size"), *InName.ToString(), *NameString);
				UE_LOG(LogTemp, Error, TEXT(" Failed to find unique name in container. Current progress: '%s' -> '%s'; NameString: %s, %d Iterations"), *InName.ToString(), *CurrentName.ToString(), *NameString, Iteration);
				break; 
			}
		}
		OutName = CurrentName;
	}
	
};
