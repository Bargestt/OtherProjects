// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectTask.h"
#include "ProjectCondition.h"
#include "HellaUtilityFunctionLibrary.h"




void UProjectTask::TestProject(UProjectObject* Project, FTaskResult& OutTestResult)
{
	FTaskResult Result;

	for (TPair<FName, UProjectCondition*>& ConditionPair : Conditions)
	{
		UProjectCondition* Condition = ConditionPair.Value;

		if (Condition)
		{
			FConditonPair ResultPair;
			ResultPair.Condition = Condition;
			ResultPair.ConditionName = ConditionPair.Key;

			if (Condition->TestProject(Project))
			{
				Result.CompletedConditions.Add(ResultPair);
			}
			else
			{
				Result.FailedConditions.Add(ResultPair);
			}
		}
	}
	OutTestResult = Result;
}

void UProjectTask::AddCondition(FName ConditionName, UProjectCondition* Condition)
{
	Conditions.Add(ConditionName, Condition);
}

FName UProjectTask::AdjustName(FName Name) const
{
	FName OutName;
	UHellaUtilityFunctionLibrary::MakeNameUniqueInContainer(Conditions, Name, OutName);
	return OutName;
}
