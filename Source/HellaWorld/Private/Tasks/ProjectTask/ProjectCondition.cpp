// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCondition.h"
#include "ProjectObject.h"





bool UProjectCondition::TestProject(UProjectObject* Project)
{
	if (!IsConditionValid()) return true; // Invalid condition is ignored

	if (!IsValid(Project))
	{
		return false;
	}	
	return TestCondition(Project);
}

bool UProjectCondition::IsConditionValid() const
{
	return false;
}

FString UProjectCondition::GetDescription()
{
	return TEXT("Project condition base class. Used to check task completion");
}


bool UProjectCondition::TestCondition(UProjectObject* Project)
{
	return true;
}


/*--------------------------------------------
 	UProjectConditionBP
 *--------------------------------------------*/


bool UProjectCondition_BlueprintBase::IsConditionValid() const
{
	return RecieveIsConditionValid();
}


FString UProjectCondition_BlueprintBase::GetDescription()
{
	return TEXT("Condition blueprint");
}

bool UProjectCondition_BlueprintBase::TestCondition(UProjectObject* Project)
{
	return RecieveTestCondition(Project);
}

bool UProjectCondition_BlueprintBase::RecieveIsConditionValid_Implementation() const
{
	return false;
}


bool UProjectCondition_BlueprintBase::RecieveTestCondition_Implementation(UProjectObject* Project)
{
	return true;
}
