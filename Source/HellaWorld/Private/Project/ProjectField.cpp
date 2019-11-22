// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectField.h"
#include "Utility/DateTimeExtension.h"



bool UProjectField_DateTime::Compare(const FDateTime& Other) const
{
	return UDateTimeExtension::CompareDateTime(Value, Other, Relevancy);
}



void UProjectField_Enum::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.Property && PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(UProjectField_Enum, EnumName))
	{
		EnumType = FindObject<UEnum>(ANY_PACKAGE, *EnumName, true);
	}
}
