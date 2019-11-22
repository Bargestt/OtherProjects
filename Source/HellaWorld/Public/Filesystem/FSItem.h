// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FSItem.generated.h"


class UFolder;

/**
 * Basic file system object
 */
UCLASS(Abstract, BlueprintType, EditInlineNew, CollapseCategories, AutoExpandCategories = (File))
class HELLAWORLD_API UFSItem : public UObject
{
	GENERATED_BODY()

private:
	//~ Folder Interface
	friend UFolder;

	void SetParent(UFolder* NewParent);


	UPROPERTY()
	UFolder* Parent;

	/** Case insensitive */
	UPROPERTY(EditInstanceOnly, Category="File")
	FName FileName;

public:

	/** Get Folder that file is in */
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|FileSystem|File")
	UFolder* GetParent() const;

	/**  Walk up the chain until root  */
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|FileSystem|File")
	UFolder* GetRoot() const;

	/** Walk up the chain until root or found parent 
	 *  @param	PotentialParent	NULL or 'this' will result in false
	 */
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|FileSystem|File")
	bool IsChildOf(UFSItem* PotentialParent) const;

	UFUNCTION(BlueprintCallable, Category = "Filesystem|FileSystem|File")
	virtual bool IsFolder() const;
	


	/** Case insensitive. Returns true if name is allowed in folder */
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|FileSystem|File")
	bool SetFileName(FString NewName);

	UFUNCTION(BlueprintCallable, Category = "HellaWorld|FileSystem|File")
	FString GetFileName() const;

	UFUNCTION(BlueprintCallable, Category = "HellaWorld|FileSystem|File")
	FName GetFileFName() const;



	/** Build path of all files including root folder */
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|FileSystem|File")
	FString GetPath(bool IncludeFilename = false) const;


	/** Create file duplicate. Adding file to folder must be done manually 
	 * @param	NewOuter	If valid, set as new outer. 
	 */
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|FileSystem|File")
	virtual UFSItem* Duplicate(UObject* NewOuter = nullptr);

	/** Delete file. File will be unusable after that */
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|FileSystem|File")
	virtual void Delete();


	// UObject Interface
	virtual void BeginDestroy() override;

protected:

	UFUNCTION(BlueprintImplementableEvent)
	void ParentChanged();

};


