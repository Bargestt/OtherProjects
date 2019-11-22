// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface.h"
#include "StylizedObjectInterface.generated.h"


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UStylizedObjectInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *	HellaOSStyle Interface
 *	Use to customize object style in more controlled manner
 */
class HELLAWORLD_API IStylizedObjectInterface
{
	GENERATED_BODY()
public:

	/** Default object style */
	UFUNCTION(BlueprintNativeEvent)
	FName GetObjectStyle() const;

	/** Return true if you want to use brush from GetCustomBrush */
	UFUNCTION(BlueprintNativeEvent)
	bool UseCustomBrush() const;

	/** Use this brush if UseCustomBrush return true */
	UFUNCTION(BlueprintNativeEvent)
	FSlateBrush GetCustomBrush();
};

