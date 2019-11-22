// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HellaObject.generated.h"

/** 
 * Object with access to the world
 * Outer must be Actor, ActorComponent or HellaObject
 */
UCLASS(Blueprintable, BlueprintType)
class HELLAWORLD_API UHellaObject : public UObject
{
	GENERATED_BODY()

public:

	// Begin UObject interface
	virtual class UWorld* GetWorld() const override;
	// End UObject interface
	
	static void SortActorsByDist(FVector Location, const TArray<AActor*>& InArr, TArray<AActor*>& OutArr, bool Inverse = false);
};