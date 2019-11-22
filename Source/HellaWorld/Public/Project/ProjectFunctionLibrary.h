// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ProjectGenerator.h"
#include "ProjectFunctionLibrary.generated.h"

class UProjectObject;

/**
 * 
 */
UCLASS(meta = (RestrictedToClasses = "ProjectGenerator"))
class HELLAWORLD_API UProjectFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()


	UFUNCTION(BlueprintPure, Category = "HellaWorld|Project|Generator", Meta = (HidePin = "NodeOwner", DefaultToSelf = "NodeOwner"))
	static UProjectObject* GetGeneratorOwner(UProjectGenerator* NodeOwner);
	
	UFUNCTION(BlueprintPure, Category = "HellaWorld|Project|Generator", Meta = (HidePin = "NodeOwner", DefaultToSelf = "NodeOwner"))
	static FProjectFieldPair CreateField_Bool(UProjectGenerator* NodeOwner, FName FieldName, bool Value);

	UFUNCTION(BlueprintPure, Category = "HellaWorld|Project|Generator", Meta = (HidePin = "NodeOwner", DefaultToSelf = "NodeOwner"))
	static FProjectFieldPair CreateField_Int(UProjectGenerator* NodeOwner, FName FieldName, int32 Value);

	UFUNCTION(BlueprintPure, Category = "HellaWorld|Project|Generator", Meta = (HidePin = "NodeOwner", DefaultToSelf = "NodeOwner"))
	static FProjectFieldPair CreateField_Float(UProjectGenerator* NodeOwner, FName FieldName, float Value);

	UFUNCTION(BlueprintPure, Category = "HellaWorld|Project|Generator", Meta = (HidePin = "NodeOwner", DefaultToSelf = "NodeOwner"))
	static FProjectFieldPair CreateField_Vector(UProjectGenerator* NodeOwner, FName FieldName, FVector Value);

	UFUNCTION(BlueprintPure, Category = "HellaWorld|Project|Generator", Meta = (HidePin = "NodeOwner", DefaultToSelf = "NodeOwner"))
	static FProjectFieldPair CreateField_Enum(UProjectGenerator* NodeOwner, FName FieldName, uint8 Value);

	UFUNCTION(BlueprintPure, Category = "HellaWorld|Project|Generator", Meta = (HidePin = "NodeOwner", DefaultToSelf = "NodeOwner"))
	static FProjectFieldPair CreateField_Name(UProjectGenerator* NodeOwner, FName FieldName, FName Value);

	UFUNCTION(BlueprintPure, Category = "HellaWorld|Project|Generator", Meta = (HidePin = "NodeOwner", DefaultToSelf = "NodeOwner"))
	static FProjectFieldPair CreateField_String(UProjectGenerator* NodeOwner, FName FieldName, FString Value);

	UFUNCTION(BlueprintPure, Category = "HellaWorld|Project|Generator", Meta = (HidePin = "NodeOwner", DefaultToSelf = "NodeOwner"))
	static FProjectFieldPair CreateField_DateTime(UProjectGenerator* NodeOwner, FName FieldName, FDateTime Value);



};
