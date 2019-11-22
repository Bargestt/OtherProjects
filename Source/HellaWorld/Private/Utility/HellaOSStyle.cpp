// Fill out your copyright notice in the Description page of Project Settings.

#include "HellaOSStyle.h"
#include "StylizedObjectInterface.h"



FSlateBrush UHellaOSStyle::GetBrush(UObject* Target, bool& Success) const
{
	FSlateBrush Brush;
	Success = false;

	if (Target)
	{
		if (Target->Implements<UStylizedObjectInterface>())
		{
			if (IStylizedObjectInterface::Execute_UseCustomBrush(Target))
			{
				Brush = IStylizedObjectInterface::Execute_GetCustomBrush(Target);
				Success = true;
			}
			else
			{
				FName StyleName = IStylizedObjectInterface::Execute_GetObjectStyle(Target);
				Success = Config.GetBrush(StyleName, Brush);
			}
		}
		else if (UClass* TargetClass = Target->GetClass())
		{
			Success = Config.GetBrush(TargetClass->GetFName(), Brush);
		}
	}

	return Brush;
}

FLinearColor UHellaOSStyle::GetColor(UObject* Target, bool& Success) const
{
	FLinearColor Color;

	Success = false;

	if (Target)
	{
		if (Target->Implements<UStylizedObjectInterface>())
		{
			FName StyleName = IStylizedObjectInterface::Execute_GetObjectStyle(Target);
			Success = Config.GetColor(StyleName, Color);
		}
		else if (UClass* TargetClass = Target->GetClass())
		{
			Success = Config.GetColor(TargetClass->GetFName(), Color);
		}
	}
	return Color;
}

USoundBase* UHellaOSStyle::GetSound(UObject* Target, bool& Success) const
{
	USoundBase* Sound = nullptr;
	Success = false;

	if (Target)
	{
		if (Target->Implements<UStylizedObjectInterface>())
		{
			FName StyleName = IStylizedObjectInterface::Execute_GetObjectStyle(Target);
			Success = Config.GetSound(StyleName, Sound);
		}
		else if (UClass* TargetClass = Target->GetClass())
		{
			Success = Config.GetSound(TargetClass->GetFName(), Sound);
		}
	}
	return Sound;
}

FSlateBrush UHellaOSStyle::GetBrushByName(FName Name, bool& Success) const
{
	FSlateBrush Brush;
	Success = Config.GetBrush(Name, Brush);
	return Brush;
}

FLinearColor UHellaOSStyle::GetColorByName(FName Name, bool& Success) const
{
	FLinearColor Color;
	Success = Config.GetColor(Name, Color);
	return Color;
}

USoundBase* UHellaOSStyle::GetSoundByName(FName Name, bool& Success) const
{
	USoundBase* Sound = nullptr;
	Success = Config.GetSound(Name, Sound);
	return Sound;
}

FName UHellaOSStyle::GetObjectStyleName(UObject* Target)
{
	FName StyleName = NAME_None;
	if (Target)
	{
		if (Target->Implements<UStylizedObjectInterface>())
		{
			if (IStylizedObjectInterface::Execute_UseCustomBrush(Target))
			{
				StyleName = FName("UseCustomBrush");
			}
			else
			{
				StyleName = IStylizedObjectInterface::Execute_GetObjectStyle(Target);
			}
		}
		else if (UClass* TargetClass = Target->GetClass())
		{
			StyleName = TargetClass->GetFName();
		}
	}
	return StyleName;
}

bool UHellaOSStyle::GetBrushFromConfig(const FHellaStyleConfig& BrushConfig, FName BrushName, FSlateBrush& OutBrush)
{
	return BrushConfig.GetBrush(BrushName, OutBrush);
}
