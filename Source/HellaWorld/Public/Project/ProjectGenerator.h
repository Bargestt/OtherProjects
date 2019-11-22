// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ProjectGenerator.generated.h"

class UProjectObject;
class UProjectField;


USTRUCT(BlueprintType)
struct FProjectFieldPair
{
	GENERATED_BODY()

	UPROPERTY()
	FName FieldName;

	UPROPERTY()
	UProjectField* Field;
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class HELLAWORLD_API UProjectGenerator : public UObject
{
	GENERATED_BODY()

	UProjectObject* ProjectBeingGenerated;
public:
	UFUNCTION(BlueprintCallable, Category="HellaWorld|Project|Generator", meta=(AdvancedDisplay="Outer"))
	UProjectObject* GenerateProject(TSubclassOf<UProjectObject> ProjectClass, UObject* Outer);

	UProjectObject* GetProject() const { return ProjectBeingGenerated; }
	
protected:
	UFUNCTION(BlueprintNativeEvent)
	TArray<FProjectFieldPair> GenerateFields();
};
