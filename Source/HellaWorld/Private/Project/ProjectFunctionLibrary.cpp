// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectFunctionLibrary.h"
#include "ProjectGenerator.h"
#include "ProjectObject.h"
#include "ProjectField.h"




UProjectObject* UProjectFunctionLibrary::GetGeneratorOwner(UProjectGenerator* NodeOwner)
{
	return NodeOwner? Cast<UProjectObject>(NodeOwner->GetOuter()) : nullptr;
}


namespace FProjectFunctionLibraryHelper
{
	template<typename Type, typename ValueType> 
	Type* CreateField(UProjectGenerator* NodeOwner, ValueType Value)
	{
		Type* Field = nullptr;
		if (NodeOwner)
		{
			if (UProjectObject* Project = NodeOwner->GetProject())
			{
				Field = NewObject<Type>(Project, NAME_None);
				Field->SetValue(Value);
			}
		}
		return Field;
	}

	template<typename Type, typename ValueType>
	FProjectFieldPair CreatePair(UProjectGenerator* NodeOwner, FName FieldName, ValueType Value)
	{
		FProjectFieldPair Pair;
		Pair.FieldName = FieldName;
		Pair.Field = CreateField<Type>(NodeOwner, Value);

		return Pair;
	}
}


FProjectFieldPair UProjectFunctionLibrary::CreateField_Bool(UProjectGenerator* NodeOwner, FName FieldName, bool Value)
{
	return FProjectFunctionLibraryHelper::CreatePair<UProjectField_Bool>(NodeOwner, FieldName, Value);
}

FProjectFieldPair UProjectFunctionLibrary::CreateField_Int(UProjectGenerator* NodeOwner, FName FieldName, int32 Value)
{
	return FProjectFunctionLibraryHelper::CreatePair<UProjectField_Int>(NodeOwner, FieldName, Value);
}

FProjectFieldPair UProjectFunctionLibrary::CreateField_Float(UProjectGenerator* NodeOwner, FName FieldName, float Value)
{
	return FProjectFunctionLibraryHelper::CreatePair<UProjectField_Float>(NodeOwner, FieldName, Value);
}

FProjectFieldPair UProjectFunctionLibrary::CreateField_Vector(UProjectGenerator* NodeOwner, FName FieldName, FVector Value)
{
	return FProjectFunctionLibraryHelper::CreatePair<UProjectField_Vector>(NodeOwner, FieldName, Value);
}

FProjectFieldPair UProjectFunctionLibrary::CreateField_Enum(UProjectGenerator* NodeOwner, FName FieldName, uint8 Value)
{
	return FProjectFunctionLibraryHelper::CreatePair<UProjectField_Enum>(NodeOwner, FieldName, Value);
}

FProjectFieldPair UProjectFunctionLibrary::CreateField_Name(UProjectGenerator* NodeOwner, FName FieldName, FName Value)
{
	return FProjectFunctionLibraryHelper::CreatePair<UProjectField_Name>(NodeOwner, FieldName, Value);
}

FProjectFieldPair UProjectFunctionLibrary::CreateField_String(UProjectGenerator* NodeOwner, FName FieldName, FString Value)
{
	return FProjectFunctionLibraryHelper::CreatePair<UProjectField_String>(NodeOwner, FieldName, Value);
}

FProjectFieldPair UProjectFunctionLibrary::CreateField_DateTime(UProjectGenerator* NodeOwner, FName FieldName, FDateTime Value)
{
	return FProjectFunctionLibraryHelper::CreatePair<UProjectField_DateTime>(NodeOwner, FieldName, Value);
}
