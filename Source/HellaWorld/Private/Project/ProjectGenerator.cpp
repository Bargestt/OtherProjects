// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectGenerator.h"
#include "ProjectObject.h"
#include "ProjectField.h"




UProjectObject* UProjectGenerator::GenerateProject(TSubclassOf<UProjectObject> ProjectClass, UObject* Outer)
{
	bool bUseOuter = IsValid(Outer);
	if (!ProjectClass)
	{
		ProjectClass = UProjectObject::StaticClass();
	}

	UProjectObject* NewProject = NewObject<UProjectObject>(bUseOuter ? Outer : GetOuter(), ProjectClass);
	ProjectBeingGenerated = NewProject; // for functions GenerateFields

	TArray<FProjectFieldPair> Fields = GenerateFields();

	for (FProjectFieldPair& Pair : Fields)
	{
		if (Pair.Field != nullptr)
		{
			if (Pair.Field->GetOuter() != NewProject)
			{
				ensureMsgf(Pair.Field->GetOuter() != NewProject, TEXT("Field outer must be created project"));
				Pair.Field->Rename(nullptr, NewProject);
			}			
			NewProject->AddField(NewProject->AdjustName(Pair.FieldName), Pair.Field);
		}
	}
	
	ProjectBeingGenerated = nullptr;
	return NewProject;
}

TArray<FProjectFieldPair> UProjectGenerator::GenerateFields_Implementation()
{
	return TArray<FProjectFieldPair>();
}
