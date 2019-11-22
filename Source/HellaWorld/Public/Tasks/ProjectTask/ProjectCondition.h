// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ProjectCondition.generated.h"

class UProjectObject;

/**
 * Project condition base class. Used to check task completion
 */
UCLASS(Abstract, BlueprintType, editinlinenew)
class HELLAWORLD_API UProjectCondition : public UObject
{
	GENERATED_BODY()

public:
	/** Test if project meets condition 
	 *  @return		True	if condition passed
	 */
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Task")
	bool TestProject(UProjectObject* Project);

	/** Check for validity of condition parameters. 
	 *  Invalid conditions will always be true
	 */
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Task")
	virtual	bool IsConditionValid() const;


	virtual FString GetDescription();
protected:
	/** @param	Project	project that is being testing */
	virtual bool TestCondition(UProjectObject* Project);

};

/** Blueprint exposed class */
UCLASS(Abstract, Blueprintable)
class HELLAWORLD_API UProjectCondition_BlueprintBase : public UProjectCondition
{
	GENERATED_BODY()
		
	
//~ Begin UProjectConditionBase Interface
public:
	virtual bool IsConditionValid() const override;
	virtual FString GetDescription() override;
protected:
	virtual bool TestCondition(UProjectObject* Project) override;
//~ End UProjectConditionBase Interface
	

	/** Invalid condition will always be true */
	UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "TestCondition"))
	bool RecieveIsConditionValid() const;
	
	UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "TestCondition"))
	bool RecieveTestCondition(UProjectObject* Project);
};
