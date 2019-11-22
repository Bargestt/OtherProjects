// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectTaskGenerator.h"
#include "ProjectTask.h"
#include "ProjectCondition.h"


UProjectTask* UProjectTaskGenerator::GenerateTask(TSubclassOf<UProjectTask> TaskClass, UObject* Outer)
{
	bool bUseOuter = IsValid(Outer);
	if (!TaskClass)
	{
		TaskClass = UProjectTask::StaticClass();
	}

	UProjectTask* NewTask = NewObject<UProjectTask>(bUseOuter ? Outer : GetOuter(), TaskClass);
	TaskBeingGenerated = NewTask; // for functions GenerateFields

	TArray<FConditionPair> Condtions = GenerateConditions();

	for (FConditionPair& Pair : Condtions)
	{
		if (Pair.Condition != nullptr)
		{
			if (Pair.Condition->GetOuter() != NewTask)
			{
				ensureMsgf(Pair.Condition->GetOuter() != NewTask, TEXT("Condition outer must be created task"));
				Pair.Condition->Rename(nullptr, NewTask);
			}
			
			NewTask->AddCondition(NewTask->AdjustName(Pair.Name), Pair.Condition);
		}
	}

	TaskBeingGenerated = nullptr;
	return NewTask;
}
