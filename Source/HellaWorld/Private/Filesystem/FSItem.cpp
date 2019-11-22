// Fill out your copyright notice in the Description page of Project Settings.

#include "FSItem.h"
#include "Folder.h"



void UFSItem::SetParent(UFolder* NewParent)
{
	if (Parent == NewParent) return;

	Parent = NewParent;	
	if (NewParent)
	{
		Rename(NULL, NewParent); // Give ownership
	}
	// If we're in the process of being garbage collected it is unsafe to call out to blueprints
	if (!HasAnyFlags(RF_BeginDestroyed) && !IsUnreachable())
	{
		ParentChanged();
	}
}

UFolder* UFSItem::GetParent() const
{
	return Parent;
}

UFolder* UFSItem::GetRoot() const
{
	UFolder* Parent = GetParent();

	if (Parent) 
	{
		while (Parent->GetParent() != nullptr)
		{
			Parent = Parent->GetParent();
		}
	}

	return Parent;
}

bool UFSItem::IsChildOf(UFSItem* PotentialParent) const
{
	if (PotentialParent == nullptr || PotentialParent == this) return false;

	const UFolder* Parent = GetParent();
	while (Parent != nullptr)
	{
		if (Parent == PotentialParent)
		{
			return true;
		}
		Parent = Parent->GetParent();
	}
	return false;
}

bool UFSItem::IsFolder() const
{
	return false;
}

bool UFSItem::SetFileName(FString NewName)
{
	UFolder* Parent = GetParent();
	if (Parent == nullptr || !Parent->ContainsFileWithName(NewName))
	{
		FileName = FName(*NewName);
		return true;
	}
	return false;
}

FString UFSItem::GetFileName() const
{
	return FileName.ToString();
}





FName UFSItem::GetFileFName() const
{
	return FileName;
}

FString UFSItem::GetPath(bool IncludeFilename /*= false*/) const
{
	UFolder* Parent = GetParent();
	FString Path = IncludeFilename ? GetFileName() : TEXT("");

	while (Parent)
	{
		Path = Parent->GetFileName() / Path;

		ensureMsgf(Parent != Parent->GetParent(), TEXT("%s Being Parent of Self is not allowed. "), *Parent->GetFileName());
		Parent = Parent->GetParent();
	}

	return Path;
}

UFSItem* UFSItem::Duplicate(UObject* NewOuter)
{	
	return NewObject<UFSItem>(NewOuter ? NewOuter : GetOuter(), GetClass(), NAME_None, RF_NoFlags, this);
}

void UFSItem::Delete()
{	
	if (UFolder* ParentFolder = GetParent())
	{
		ParentFolder->RemoveFile(this);
	}	
	this->MarkPendingKill();
}

void UFSItem::BeginDestroy()
{
	if (UFolder* ParentFolder = GetParent())
	{
		ParentFolder->RemoveFile(this);
	}
	Super::BeginDestroy();
}

