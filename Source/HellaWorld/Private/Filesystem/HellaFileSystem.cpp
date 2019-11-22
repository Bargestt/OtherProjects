// Fill out your copyright notice in the Description page of Project Settings.

#include "HellaFileSystem.h"


#include "File.h"
#include "FSItem.h"
#include "Folder.h"

DEFINE_LOG_CATEGORY(HellaFileSystem);


UHellaFileSystem::UHellaFileSystem()
{
	DefaultFileClass = UFile::StaticClass();
	DefaultFolderClass = UFolder::StaticClass();
}

UFolder* UHellaFileSystem::GetRoot()
{
	if (Root == nullptr)
	{
		Root = NewObject<UFolder>(this, NAME_None);
	}
	if (Root->GetFileFName() != GetFName())
	{
		Root->SetFileName(GetName());
	}

	return Root;
}



void UHellaFileSystem::SetDefaultFolderClass(TSubclassOf<UFolder> NewClass)
{
	DefaultFolderClass = NewClass ? NewClass : UFolder::StaticClass();
}

void UHellaFileSystem::SetDefaultFileClass(TSubclassOf<UFile> NewClass)
{
	DefaultFolderClass = NewClass ? NewClass : UFile::StaticClass();
}

TSubclassOf<UFolder> UHellaFileSystem::GetDefaultFolderClass() const
{
	return DefaultFolderClass;
}

TSubclassOf<UFile> UHellaFileSystem::GetDefaultFileClass() const
{
	return DefaultFileClass;
}

UFile* UHellaFileSystem::CreateFileOfType(FString Path, FString FileName, TSubclassOf<UFile> Type)
{
	UFile* File = NewObject<UFile>(this, Type, NAME_None);
	File->SetFileName(FileName);

	if (UFolder* Folder = CreatePath(Path))
	{
		Folder->AddFile(File);
	}
	else
	{
		GetRoot()->AddFile(File);
	}

	UE_LOG(LogTemp, Warning, TEXT("Parent %s"), File->GetParent() ? *File->GetParent()->GetFileName() : TEXT("NULL"));

	return File;
}






UFile* UHellaFileSystem::CreateFile(FString Path, FString FileName, UObject* Asset)
{
	UFile* AssetFile = (UFile*) CreateFileOfType(Path, FileName, GetDefaultFileClass());	
	AssetFile->SetAsset(Asset);

	return AssetFile;
}

UFolder* UHellaFileSystem::CreatePath(FString Path)
{
	TArray<FString> Folders;
	Path.ParseIntoArray(Folders, TEXT("/"), true);		

	if (Folders.Num() <= 0)
	{
		return GetRoot();
	}

	UFolder* CurrentFolder = GetRoot();

	for (int Index = 0; Index < Folders.Num() ; Index++)
	{
		FString FolderName = Folders[Index];

		UFolder* NextFolder = Cast<UFolder>(CurrentFolder->GetFileByName(FolderName));
		if (NextFolder == nullptr)
		{
			NextFolder = CreateFolderIsolated(FolderName);
			CurrentFolder->AddFile(NextFolder);
		}
		CurrentFolder = NextFolder;
	}

	return CurrentFolder;
}



UFile* UHellaFileSystem::CreateFileIsolated(UObject* Asset, FString FileName /*= TEXT("NewFile")*/) const
{
	UFile* File = NewObject<UFile>((UObject*)this, GetDefaultFileClass(), NAME_None);
	File->SetFileName(FileName);
	File->SetAsset(Asset);

	return File;
}

UFolder* UHellaFileSystem::CreateFolderIsolated(FString FolderName /*= TEXT("NewFolder")*/) const
{
	UFolder* Folder = NewObject<UFolder>((UObject*)this, GetDefaultFolderClass(), NAME_None);
	Folder->SetFileName(FolderName);

	return Folder;
}

 void UHellaFileSystem::GetDebugPaths(TArray<FString>& OutPaths) const
 {
	 if (Root)
	 {
		 OutPaths.Empty();
		 OutPaths = Root->GetDebugPaths(true);
	 }
 }

 UHellaFileSystem* UHellaFileSystem::GetDuplicate(UObject* NewOuter)
 {
	 UHellaFileSystem* NewSystem = NewObject<UHellaFileSystem>(NewOuter, NAME_None);
	 if (Root)
	 {
		 NewSystem->Root = (UFolder*)Root->Duplicate(NewSystem);
	 }

	 return NewSystem;
 }

bool UHellaFileSystem::Reinitialize_Implementation(const UObject* Template)
{
	const UHellaFileSystem* TemplateSystem = Cast<UHellaFileSystem>(Template);

	if (TemplateSystem->Root) 
	{
		Root = (UFolder*)TemplateSystem->Root->Duplicate(this);
	}
	GetRoot();

	return true;
}

