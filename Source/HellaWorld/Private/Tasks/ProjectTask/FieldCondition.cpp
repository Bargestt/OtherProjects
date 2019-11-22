// Fill out your copyright notice in the Description page of Project Settings.

#include "FieldCondition.h"
#include "ProjectObject.h"
#include "ProjectField.h"


/*--------------------------------------------
 	UFieldConditionBase
 *--------------------------------------------*/

bool UFieldConditionBase::IsConditionValid() const
{
	return false;
}

FString UFieldConditionBase::GetDescription()
{
	return TEXT("Condition for project field");
}

/*--------------------------------------------
 	UConditionFieldMatch
 *--------------------------------------------*/

bool UConditionFieldMatch::IsConditionValid() const
{
	return TargetField != NAME_None && IsValid(Field);
}

FString UConditionFieldMatch::GetDescription()
{
	return TEXT("Target field must match field in condition exactly");
}

bool UConditionFieldMatch::TestCondition(UProjectObject* Project)
{
	UProjectField* ProjectField = Project->GetField(TargetField);
	return ProjectField ? ProjectField->IsEqual(Field) : false;
}

/*--------------------------------------------
 	UConditionFieldSet
 *--------------------------------------------*/

bool UConditionFieldSet::IsConditionValid() const
{
	if (TargetField != NAME_None && Fields.Num() > 0)
	{
		for (UProjectField* Field : Fields)
		{
			if (IsValid(Field)) return true;
		}
	}
	return false;
}

FString UConditionFieldSet::GetDescription()
{
	return TEXT("Test field must match on of the fields in the condition");
}

bool UConditionFieldSet::TestCondition(UProjectObject* Project)
{
	UProjectField* ProjectField = Project->GetField(TargetField);

	if (ProjectField) 
	{
		for (UProjectField* Field : Fields)
		{
			if (ProjectField->IsEqual(Field))
			{
				return true;
			}
		}
	}
	return false;
}
