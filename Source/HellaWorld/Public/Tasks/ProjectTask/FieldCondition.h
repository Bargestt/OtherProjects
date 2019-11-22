// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectCondition.h"
#include "FieldCondition.generated.h"

class UProjectField;

UCLASS(Abstract)
class HELLAWORLD_API UFieldConditionBase : public UProjectCondition
{
	GENERATED_BODY()
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Condition")
	FName TargetField;

public:
	virtual bool IsConditionValid() const override;
	virtual FString GetDescription() override;
};


UCLASS()
class HELLAWORLD_API UConditionFieldMatch : public UFieldConditionBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "Condition")
	UProjectField* Field;

public:
	virtual bool IsConditionValid() const override;
	virtual FString GetDescription() override;
protected:
	virtual bool TestCondition(UProjectObject* Project) override;
};



UCLASS()
class HELLAWORLD_API UConditionFieldSet : public UFieldConditionBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "Condition")
	TArray<UProjectField*> Fields;

public:
	virtual bool IsConditionValid() const override;
	virtual FString GetDescription() override;
protected:
	virtual bool TestCondition(UProjectObject* Project) override;
};
