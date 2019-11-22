// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FSItem.h"
#include "Folder.generated.h"


/**
 * Basic folder
 */
UCLASS(Blueprintable)
class HELLAWORLD_API UFolder : public UFSItem
{
	GENERATED_BODY()

	UPROPERTY(Instanced)
	TArray<UFSItem*> Files;
public:

	/** Add file to folder. Filename will be adjusted if needed
	 * @return true if file was added successfully or it's already in folder
	 */
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|FileSystem|File")
	bool AddFile(UFSItem* File);

	/** Remove file from folder. File will not be deleted */
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|FileSystem|File")
	void RemoveFile(UFSItem* File);

	/** Remove all files from folder. Files will not be deleted */
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|FileSystem|File")
	void RemoveAllFiles();

	/** Delete all files in folder. Files will be lost after that */
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|FileSystem|File")
	void DeleteAllFiles();



	/** Check if folder has this file */
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|FileSystem|File")
	bool Contains(UFSItem* Other, bool bCheckSubfolders = false) const;

	/** Does not include subfolders */
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|FileSystem|File")
	int FilesNum() const;


	UFUNCTION(BlueprintCallable, Category = "HellaWorld|FileSystem|File")
	TArray<UFSItem*> GetFiles(bool bIncludeSubFolders = false) const;

	UFUNCTION(BlueprintCallable, Category = "HellaWorld|FileSystem|File")
	TArray<FString> GetDebugPaths(bool bIncludeSubFolders = false) const;


	UFUNCTION(BlueprintCallable, Category = "HellaWorld|FileSystem|File")
	bool ContainsFileWithName(FString Name, bool bCheckSubfolders = false) const;

	UFUNCTION(BlueprintCallable, Category = "HellaWorld|FileSystem|File")
	UFSItem* GetFileByName(FString SearchName, bool bCheckSubfolders = false) const;

	UFSItem* GetFileByFName(FName SearchName, bool bCheckSubfolders = false) const;


	/** Add numbers to the end of file until name is valid */
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|FileSystem|File")
	FString FixFileName(FString Name) const;

	/** Check tree for errors and fix them
	 *	@return true if no error was found
	 */
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|FileSystem|File")
	bool UpdateTree();

	//~ FSItem interface
	virtual UFSItem* Duplicate(UObject* NewOuter = nullptr) override;
	virtual void Delete() override;

	virtual bool IsFolder() const override;

protected:

	UFUNCTION(BlueprintImplementableEvent)
	void ChildrenChanged();



};