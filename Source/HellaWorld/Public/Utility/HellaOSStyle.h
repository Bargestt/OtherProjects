// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HellaOSStyle.generated.h"







USTRUCT(BlueprintType)
struct FHellaStyleConfig
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, FSlateBrush> Icons;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, FLinearColor> Colors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, USoundBase*> Sounds;
	

	bool GetBrush(FName BrushName, FSlateBrush& OutBrush) const
	{
		RemoveClassSuffix(BrushName);
		if (const FSlateBrush* Brush = Icons.Find(BrushName))
		{
			OutBrush = *Brush;
			return true;
		}

		return false;
	}

	bool GetColor(FName ColorName, FLinearColor& OutColor) const
	{
		RemoveClassSuffix(ColorName);
		if (const FLinearColor* Color = Colors.Find(ColorName))
		{
			OutColor = *Color;
			return true;
		}

		return false;
	}

	bool GetSound(FName SoundName, USoundBase* OutSound) const
	{
		RemoveClassSuffix(SoundName);

		if (Sounds.Contains(SoundName)) //don't want USoundBase* const* hell here
		{
			OutSound = Sounds[SoundName];
			return true;
		}

		return false;
	}

	static void RemoveClassSuffix(FName& Name)
	{
		FString NameStr = Name.ToString();
		if (NameStr.RemoveFromEnd(TEXT("_C"))) // Remove blueprint suffix
		{
			Name = FName(*NameStr);
		}
	}
};

/**
 * 
 */
UCLASS(BlueprintType, autoExpandCategories="Config", collapseCategories)
class HELLAWORLD_API UHellaOSStyle : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	FHellaStyleConfig Config;
	
	/**
	 * Get style brush for object based on class name or StylizedObjectInterface info
	 * @return	style assigned brush or default brush if not style found
	 */
	UFUNCTION(BlueprintCallable, Category="HellaWorld|Style")
	FSlateBrush GetBrush(UObject* Target, bool& Success) const;

	/**
	 * Get color associated with object style based on class name or StylizedObjectInterface info
	 */
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Style")
	FLinearColor GetColor(UObject* Target, bool& Success) const;

	/**
	 * Get sound associated with object style based on class name or StylizedObjectInterface info
	 */
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Style")
	USoundBase* GetSound(UObject* Target, bool& Success) const;

	/** Config getter for convenience */
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Style")
	FSlateBrush GetBrushByName(FName Name, bool& Success) const;

	/** Config getter for convenience */
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Style")
	FLinearColor GetColorByName(FName Name, bool& Success) const;

	/** Config getter for convenience */
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Style")
	USoundBase* GetSoundByName(FName Name, bool& Success) const;


	/**
	 * Get StyleName for object based on class name or StylizedObjectInterface info
	 * @return	StyleName / "UseCustomBrush" if brush is customized by asset / None object is invalid
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HellaWorld|Style")
	static FName GetObjectStyleName(UObject* Target);

	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Style")
	static bool GetBrushFromConfig(const FHellaStyleConfig& BrushConfig, FName BrushName, FSlateBrush& OutBrush);
};
