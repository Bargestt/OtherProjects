// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ProjectTaskGenerator.generated.h"

class UProjectTask;
class UProjectCondition;


/**  */
USTRUCT(BlueprintType)
struct FConditionPair
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FName Name;

	UPROPERTY(BlueprintReadWrite)
	UProjectCondition* Condition;
};


/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class HELLAWORLD_API UProjectTaskGenerator : public UObject
{
	GENERATED_BODY()

	UProjectTask* TaskBeingGenerated;

public:
	UFUNCTION(BlueprintCallable, Category="HellaWorld|Task", meta = (AdvancedDisplay = "Outer"))
	UProjectTask* GenerateTask(TSubclassOf<UProjectTask> TaskClass, UObject* Outer);
	
	UProjectTask* GetTaskBeingGenerated() const { return TaskBeingGenerated; }
	
protected:
	UFUNCTION(BlueprintImplementableEvent)
	TArray<FConditionPair> GenerateConditions();
};

