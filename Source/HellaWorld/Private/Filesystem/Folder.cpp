// Fill out your copyright notice in the Description page of Project Settings.

#include "Folder.h"
#include "HellaFileSystem.h"



bool UFolder::AddFile(UFSItem* Child)
{
	if (!IsValid(Child)) return false;
	if (Child == this) return false;
	if (IsChildOf(Child))
	{
		UE_LOG(HellaFileSystem, Error, TEXT("Can't add %s to %s. %s Is parent of %s'"), *Child->GetName(), *GetName(), *Child->GetName(), *GetName());
		return false;
	}

	if (Files.Contains(Child)) return true;

	if (UFolder* OldParent = Child->GetParent())
	{
		OldParent->Files.RemoveSingle(Child);
	}

	Child->SetFileName(FixFileName(Child->GetFileName()));
	Files.Add(Child);	
	Child->SetParent(this);

	ChildrenChanged();

	return true;
}

void UFolder::RemoveFile(UFSItem* File)
{	
	if (File)
	{
		Files.RemoveSingle(File);
		File->SetParent(nullptr);

		// If we're in the process of being garbage collected it is unsafe to call out to blueprints
		if (!HasAnyFlags(RF_BeginDestroyed) && !IsUnreachable())
		{
			ChildrenChanged();
		}
	}
}



void UFolder::RemoveAllFiles()
{
	for (UFSItem* File : Files)
	{
		if (File)
		{
			File->SetParent(nullptr);
		}
	}
	Files.Empty();
	ChildrenChanged();
}

void UFolder::DeleteAllFiles()
{
	for (UFSItem* File : Files)
	{
		if (File)
		{
			File->Parent = nullptr; // prevent from changing array during loop
			File->Delete(); // Mark pending kill
		}
	}
	Files.Empty();
	ChildrenChanged();
}


bool UFolder::Contains(UFSItem* Other, bool bCheckSubfolders /*= false*/) const
{
	if (Other == nullptr) return false;

	bool bContains = Files.Contains(Other);

	if (!bContains && bCheckSubfolders)
	{
		for (const UFSItem* File : Files)
		{
			if (const UFolder* AsFolder = Cast<UFolder>(File))
			{				
				if (AsFolder->Contains(Other, bCheckSubfolders))
				{
					return true;
				}
			}
		}
	}

	return bContains;
}

int UFolder::FilesNum() const
{
	return Files.Num();
}



TArray<UFSItem*> UFolder::GetFiles(bool bIncludeSubFolders /*= false*/) const
{
	TArray<UFSItem*> FileArray;
	FileArray.Append(Files);

	if (bIncludeSubFolders)
	{
		for (const UFSItem* File : Files)
		{
			if (const UFolder* AsFolder = Cast<UFolder>(File))
			{
				FileArray.Append(AsFolder->GetFiles(bIncludeSubFolders));
			}
		}
	}

	return FileArray;
}


TArray<FString> UFolder::GetDebugPaths(bool bIncludeSubFolders /*= false*/) const
{
	TArray<FString> Paths;	
	FString FolderPath = GetPath(true);
	for (UFSItem* File : Files)
	{
		if (File)
		{			
			FString FilePath = FolderPath / File->GetFileName();
			FString ClassName = File->GetClass() ? File->GetClass()->GetName() : TEXT("None");			
			FString OuterName = TEXT("None");
			if (UObject* FileOuter = File->GetOuter())
			{
				if (UFSItem* OuterAsFile = Cast<UFSItem>(FileOuter))
				{
					OuterName = OuterAsFile->GetFileName();
				}
				else {
					OuterName = FileOuter->GetName() + TEXT(" (err)");
				}
			}

			Paths.Add(FString::Printf(TEXT("%s '%s' Outer: %s"), *FilePath, *ClassName, *OuterName));

			if (UFolder* AsFolder = Cast<UFolder>(File))
			{
				Paths.Append(AsFolder->GetDebugPaths(bIncludeSubFolders));
			}
		}
	}

	return Paths;
}

bool UFolder::ContainsFileWithName(FString Name, bool bCheckSubfolders /*= false*/) const
{
	return GetFileByName(Name) ? true : false;
}

UFSItem* UFolder::GetFileByName(FString SearchName, bool bCheckSubfolders /*= false*/) const
{
	FName Name = FName(*SearchName); 
	return GetFileByFName(Name);
}

UFSItem* UFolder::GetFileByFName(FName SearchName, bool bCheckSubfolders /*= false*/) const
{
	for (UFSItem* File : Files)
	{
		if (File && File->FileName == SearchName)
		{
			return File;
		}
	}

	if (bCheckSubfolders)
	{
		for (const UFSItem* File : Files)
		{
			if (const UFolder* AsFolder = Cast<UFolder>(File))
			{
				if (UFSItem* FoundFile = AsFolder->GetFileByFName(SearchName))
				{
					return FoundFile;
				}
			}
		}
	}

	return nullptr;
}

FString UFolder::FixFileName(FString Name) const
{
	if (ContainsFileWithName(Name))
	{
		TSet<FName> Names;
		for (UFSItem* ChildFile : Files)
		{
			if (ChildFile)
			{
				Names.Add(ChildFile->FileName);
			}
		}	
		FName Test = *(Name + TEXT("_1"));
		for (int Index = 1; Index < 1000 ; Index++)
		{
			if (!Names.Contains(Test))
			{
				Name = Test.ToString();
				break;
			}
			Test = *(Name + TEXT("_") + FString::FromInt(Index));
		}
	}
	return Name;
}

bool UFolder::UpdateTree()
{
	bool IsTreeValid = true;
	int32 RemovedNum = Files.RemoveAll([](const UFSItem* File) { return !IsValid(File); });
	if (RemovedNum > 0)
	{
		MarkPackageDirty();
		UE_LOG(HellaFileSystem, Warning, TEXT("Removed %d null object from folder %s"), RemovedNum, *GetPath(true));
		IsTreeValid = false;
	}

	for (UFSItem* Child : Files)
	{		
		if (Child->Parent != this)
		{
			UE_LOG(HellaFileSystem, Warning, TEXT("Fixed parent in %s from %s to %s"), 
				*Child->GetFileName(), Child->GetParent()? *Child->GetParent()->GetFileName(): TEXT("None"), *this->GetFileName() );
			Child->SetParent(this);

			
			MarkPackageDirty();
			IsTreeValid = false;
		}
		
		if (UFolder* AsFolder = Cast<UFolder>(Child))
		{
			AsFolder->UpdateTree();
		}		
	}
	
	return IsTreeValid;
}

UFSItem* UFolder::Duplicate(UObject* NewOuter /*= nullptr*/)
{
	UFolder* NewFolder = NewObject<UFolder>(NewOuter ? NewOuter : GetOuter(), NAME_None, RF_NoFlags, this);
	return NewFolder;
}


void UFolder::Delete()
{
	DeleteAllFiles();
	Super::Delete();
}

bool UFolder::IsFolder() const
{
	return true;
}

