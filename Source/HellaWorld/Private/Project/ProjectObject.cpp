// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectObject.h"
#include "ProjectField.h"
#include "HellaUtilityFunctionLibrary.h"



void UProjectObject::CreateField(UProjectObject*& Project, TSubclassOf<UProjectField> Class, UProjectField*& CreatedField)
{
	CreatedField = (Project && Class) ? NewObject<UProjectField>((UObject*)Project, Class, NAME_None) : nullptr;
}



void UProjectObject::SetTemplate(const FProjectObjectTemplate& Template)
{
	ClearFields();

	Fields.Reserve(Template.Fields.Num());
	ProjectName = Template.ProjectName;
	for (const FProjectObjectFieldTemplate& FieldTemplate : Template.Fields)
	{
		if (Fields.Contains(FieldTemplate.FieldName))
		{
			continue;
		}		
		if (UProjectField* NewField = NewObject<UProjectField>((UObject*)this, FieldTemplate.FieldType, NAME_None))
		{
			Fields.Add(FieldTemplate.FieldName, NewField);
		}
	}
}

bool UProjectObject::IsEqualTo(const UProjectObject* Other, bool StrictCompare /*= true*/) const
{
	if (Other == nullptr) return false;
	if (Other == this) return true;

	if (StrictCompare && this->Fields.Num() != Other->Fields.Num()) return false;

	for (const TPair<FName, UProjectField*>& Pair : Fields)
	{
		const UProjectField* OtherField = Other->GetField(Pair.Key);

		if (OtherField && OtherField->IsEqual(Pair.Value))
		{
			continue;
		}		
		return false;		
	}

	return true;
}




TArray<FName> UProjectObject::GetEqualFields(const UProjectObject* Other, bool IgnoreFieldValues /*= false*/) const
{
	TArray<FName> MatchingFields;
	if (Other == nullptr) return MatchingFields;

	if (Other == this)
	{
		Fields.GenerateKeyArray(MatchingFields);
		return MatchingFields;
	}

	for (const TPair<FName, UProjectField*>& Pair : Fields)
	{
		FName FieldName = Pair.Key;

		const UProjectField* CurrentField = Pair.Value;
		const UProjectField* OtherField = Other->GetField(FieldName);

		if (CurrentField == nullptr && OtherField == nullptr)
		{
			MatchingFields.Add(FieldName);
			continue;
		}

		if (IgnoreFieldValues)
		{
			if (CurrentField->IsSameDataType(OtherField))
			{
				MatchingFields.Add(FieldName);
			}
		}
		else
		{
			if (CurrentField->IsEqual(OtherField))
			{
				MatchingFields.Add(FieldName);
			}
		}
	}
	return MatchingFields;
}


void UProjectObject::GetFieldsOfType(TSubclassOf<UProjectField> Type, TArray<UProjectField*>& OutFields, TArray<FName>& OutNames)
{
	OutFields.Reset(Fields.Num());
	OutNames.Reset(Fields.Num());

	const UClass* TargetClass = Type;
	for (TPair<FName, UProjectField*>& Pair : Fields)
	{
		UProjectField* Field = Pair.Value;
		if (Field && Field->IsA(TargetClass))
		{
			OutFields.Add(Field);
			OutNames.Add(Pair.Key);
		}
	}
}

TArray<FProjectFieldData> UProjectObject::GetFields() 
{
	TArray<FProjectFieldData> Array;
	Array.Reserve(Fields.Num());
	for (const TPair<FName, UProjectField*>& Pair : Fields)
	{
		UProjectField* Field = Pair.Value;
		Array.Add({ Pair.Key, Field ? Field->GetClass() : nullptr, Field });
	}

	return Array;
}

FName UProjectObject::AdjustName(FName Name) const
{
	FName OutName;
	UHellaUtilityFunctionLibrary::MakeNameUniqueInContainer(Fields, Name, OutName);
	return OutName;
}

void UProjectObject::AddField(FName FieldName, UProjectField* Field)
{
	Fields.Add(FieldName, Field);
}


void UProjectObject::GetField(FName FieldName, UProjectField*& Field, bool& HasField)
{
	UProjectField ** FieldPtr = Fields.Find(FieldName);
	Field = FieldPtr ? *FieldPtr : nullptr;
	HasField = FieldPtr != nullptr;
}




UProjectField* UProjectObject::GetField(FName FieldName)
{
	UProjectField ** FieldPtr = Fields.Find(FieldName);
	return FieldPtr ? *FieldPtr : nullptr;
}

const UProjectField* UProjectObject::GetField(FName FieldName) const
{
	const UProjectField * const* FieldPtr = Fields.Find(FieldName);
	return FieldPtr ? *FieldPtr : nullptr;
}

TSubclassOf<UProjectField> UProjectObject::GetFieldType(FName FieldName) const
{
	const UProjectField* Field = GetField(FieldName);
	return Field ? Field->GetClass() : nullptr;
}

void UProjectObject::ClearFields()
{
	for (const TPair<FName, UProjectField*>& Pair : Fields)
	{
		if (UProjectField* Field = Pair.Value)
		{
			Field->MarkPendingKill();
		}
	}
	Fields.Empty();
}

void UProjectObject::ResetFields()
{
	for (const TPair<FName, UProjectField*>& Pair : Fields)
	{
		if (UProjectField* Field = Pair.Value) 
		{
			Field->Reset();
		}
	}
}





void UProjectObject::SetField_AsBool(FName FieldName, bool Value, bool ForceCast /*= false*/)
{
	SetField<UProjectField_Bool>(FieldName, Value, ForceCast);
}

void UProjectObject::SetField_AsInt(FName FieldName, int32 Value, bool ForceCast /*= false*/)
{
	SetField<UProjectField_Int>(FieldName, Value, ForceCast);
}

void UProjectObject::SetField_AsFloat(FName FieldName, float Value, bool ForceCast /*= false*/)
{
	SetField<UProjectField_Float>(FieldName, Value, ForceCast);
}

void UProjectObject::SetField_AsVector(FName FieldName, FVector Value, bool ForceCast /*= false*/)
{
	SetField<UProjectField_Vector>(FieldName, Value, ForceCast);
}

void UProjectObject::SetField_AsEnum(FName FieldName, uint8 Value, bool ForceCast /*= false*/)
{
	SetField<UProjectField_Enum>(FieldName, Value, ForceCast);
}

void UProjectObject::SetField_AsName(FName FieldName, FName Value, bool ForceCast /*= false*/)
{
	SetField<UProjectField_Name>(FieldName, Value, ForceCast);
}

void UProjectObject::SetField_AsString(FName FieldName, FString Value, bool ForceCast /*= false*/)
{
	SetField<UProjectField_String>(FieldName, Value, ForceCast);
}

void UProjectObject::SetField_AsDateTime(FName FieldName, FDateTime Value, bool ForceCast /*= false*/)
{
	SetField<UProjectField_DateTime>(FieldName, Value, ForceCast);
}



void UProjectObject::GetField_AsBool(FName FieldName, bool& Value, bool& Success) const
{
	GetFieldValue<UProjectField_Bool>(FieldName, Value, Success);
}

void UProjectObject::GetField_AsInt(FName FieldName, int32& Value, bool& Success) const
{
	GetFieldValue<UProjectField_Int>(FieldName, Value, Success);
}

void UProjectObject::GetField_AsFloat(FName FieldName, float& Value, bool& Success) const
{
	GetFieldValue<UProjectField_Float>(FieldName, Value, Success);
}

void UProjectObject::GetField_AsVector(FName FieldName, FVector& Value, bool& Success) const
{
	GetFieldValue<UProjectField_Vector>(FieldName, Value, Success);
}

void UProjectObject::GetField_AsEnum(FName FieldName, uint8& Value, bool& Success) const
{
	GetFieldValue<UProjectField_Enum>(FieldName, Value, Success);
}

void UProjectObject::GetField_AsName(FName FieldName, FName& Value, bool& Success) const
{
	GetFieldValue<UProjectField_Name>(FieldName, Value, Success);
}

void UProjectObject::GetField_AsString(FName FieldName, FString& Value, bool& Success) const
{
	GetFieldValue<UProjectField_String>(FieldName, Value, Success);
}

void UProjectObject::GetField_AsDateTime(FName FieldName, FDateTime& Value, bool& Success) const
{
	GetFieldValue<UProjectField_DateTime>(FieldName, Value, Success);
}



bool UProjectObject::Reinitialize_Implementation(const UObject* Template)
{
	const UProjectObject* TemplateObject = Cast<UProjectObject>(Template);

	ClearFields();

	for (const TPair<FName, UProjectField*>& Pair : TemplateObject->Fields)
	{
		UProjectField* Original = Pair.Value;
		UProjectField* FieldCopy = nullptr;
		if (Original) 
		{
			FieldCopy = NewObject<UProjectField>(this, Original->GetClass(), NAME_None, RF_NoFlags, Original);	
			
		}
		AddField(Pair.Key, FieldCopy);
	}

	return true;
}
