// Fill out your copyright notice in the Description page of Project Settings.

#include "HellaFileUtilityFunctionLibrary.h"
#include "FSItem.h"




void UHellaFileUtilityFunctionLibrary::SortFiles(const TArray<UFSItem*>& InFiles, TArray<UFSItem*>& OutFiles, FFileSortParameters Parameters)
{
	OutFiles.Reset(InFiles.Num());
	for (UFSItem* File : InFiles)
	{
		if (File)
		{
			OutFiles.Add(File);
		}
	}

	auto SortPredicate = [Parameters](const UFSItem* A, const UFSItem* B)
	{
		bool ABeforeB = false;

		if (Parameters.SeparateFilesAndFolders && A->IsFolder() != B->IsFolder())
		{
			if (A->IsFolder())
			{
				ABeforeB = true;
			}
			else
			{
				ABeforeB = false;
			}
		}
		else 
		{
			switch (Parameters.SortBy)
			{
			case ESortFeature::Name:
				ABeforeB = A->GetFileName() < B->GetFileName();
				break;
			default:
				ensureMsgf(false, TEXT("Please implement logic for this enum (as Int)ESortFeature::%d"), (int)Parameters.SortBy);
				break;
			}
		}

		if (Parameters.SortOrder == EOrder::Order_Descending)
		{
			ABeforeB = !ABeforeB;
		}
		return ABeforeB;
	};

	Algo::Sort(OutFiles, SortPredicate);	
}


