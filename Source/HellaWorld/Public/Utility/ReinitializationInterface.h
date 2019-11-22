// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ReinitializationInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UReinitializationInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Reinitialize sub-objects and properties using passed object as template
 */
class HELLAWORLD_API IReinitializationInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
protected:
	/**
	 * Reinitialize sub-objects and properties using passed object as template
	 * Template is checked for NULL and Class already
	 * @return true if was successful
	 */
	UFUNCTION(BlueprintNativeEvent)
	bool Reinitialize(const UObject* Template);

};

/**
 *
 */
UCLASS()
class HELLAWORLD_API UReinitializationFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * Reinitialize sub-objects and properties using passed object as template
	 * Target must implement IReinitializationInterface
	 * Template must be subclass of Target
	 * @param	Target	Object that will be reinitialized
	 * @param	Template	Must be subclass of Target
	 * @return	false	If reinitialization function failed or wasn't called
	 */
	UFUNCTION(BlueprintCallable, Category="HellaWorld|Utility")
	static bool ReinitializeObject(UObject* Target, const UObject* Template)
	{
		if (Template && Target && Template->IsA(Target->GetClass())  && Target->Implements<UReinitializationInterface>())
		{
			return IReinitializationInterface::Execute_Reinitialize(Target, Template);
		}
		return false;
	}


	/** 
	 *  Standard duplication
	 *  Use if Template has proper outer chain otherwise shallow copy could happen
	 *  Subobjects with Outer pointing to Template will be duplicated too
	 */
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Utility")
	static UObject* DuplicateObject(UObject* DuplicateOuter, UObject* Template, FName NewName = NAME_None)
	{
		UObject* Duplicate = nullptr;
		if (DuplicateOuter && Template)
		{						
			FObjectDuplicationParameters Params(Template, DuplicateOuter);
			Params.DestName = NewName;

#if !UE_BUILD_SHIPPING
			// Debug display duplication
			TMap<UObject *, UObject *> Info;
			Params.CreatedObjects = &Info;
#endif // !UE_BUILD_SHIPPING
			Duplicate = StaticDuplicateObjectEx(Params);

#if !UE_BUILD_SHIPPING
			// Debug display duplication
			// align output for readability
			TArray<TTuple<FString, FString>> Paths;
			int32 LongestPath = 0;
			for (TPair<UObject*, UObject*>& Pair : Info)
			{
				FString OriginalPath = Pair.Key->GetPathName();
				if (OriginalPath.Len() > LongestPath)
				{
					LongestPath = OriginalPath.Len();
				}
			}
			for (TPair<UObject*, UObject*>& Pair : Info)
			{	
				FString OriginalPath = Pair.Key->GetPathName();
				FString CopyPath = Pair.Value->GetPathName();
				FString Fill = FString::ChrN(LongestPath - OriginalPath.Len() + 1, '-');
				UE_LOG(LogTemp, Warning, TEXT("Duplicated: %s %s> %s"), *OriginalPath, *Fill, *CopyPath);
			}			
#endif // !UE_BUILD_SHIPPING
		}

		return Duplicate;
	}
};