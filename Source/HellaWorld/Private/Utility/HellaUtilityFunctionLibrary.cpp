// Fill out your copyright notice in the Description page of Project Settings.

#include "HellaUtilityFunctionLibrary.h"






void UHellaUtilityFunctionLibrary::SortStringArray(const TArray<FString>& InArray, TArray<FString>& OutArray, bool Ascending /*= true*/)
{
	OutArray = InArray;
	SortStringArrayByRef(OutArray, Ascending);
}

void UHellaUtilityFunctionLibrary::SortStringArrayByRef(TArray<FString>& TargetArray, bool Ascending /*= true*/)
{
	if (Ascending)
	{
		TargetArray.StableSort([](const FString& A, const FString& B) { return A < B; });
	}
	else
	{
		TargetArray.StableSort([](const FString& A, const FString& B) { return A > B; });
	}
}

void UHellaUtilityFunctionLibrary::MakeNameUniqueInArray(const TArray<FName>& NameArray, FName InName, FName& OutName)
{
	if (NameArray.Num() <= 0)
	{
		OutName = InName;
		return;
	}
	MakeNameUniqueInContainer(TSet<FName>(NameArray), InName, OutName);
}

