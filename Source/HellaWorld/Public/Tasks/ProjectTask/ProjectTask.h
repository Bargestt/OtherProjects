// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ProjectTask.generated.h"

class UProjectObject;
class UProjectField;
class UProjectCondition;

USTRUCT(BlueprintType)
struct FConditonPair
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FName ConditionName;

	UPROPERTY(BlueprintReadWrite)
	UProjectCondition* Condition;
};

USTRUCT(BlueprintType)
struct FTaskResult
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	TArray<FConditonPair> CompletedConditions;

	UPROPERTY(BlueprintReadOnly)
	TArray<FConditonPair> FailedConditions;
};

/**
 * Condition aggregator
 */
UCLASS(BlueprintType, Blueprintable)
class HELLAWORLD_API UProjectTask : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	TMap<FName, UProjectCondition*> Conditions;

	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Task")
	void TestProject(UProjectObject* Project, FTaskResult& OutTestResult);

	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Task")
	void AddCondition(FName ConditionName, UProjectCondition* Condition);

	/** Make name unique in conditions */
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Task")	
	FName AdjustName(FName Name) const;
};
