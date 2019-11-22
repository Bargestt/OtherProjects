// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ReinitializationInterface.h"
#include "HellaFileSystem.generated.h"

class UFile;
class UFolder;

DECLARE_LOG_CATEGORY_EXTERN(HellaFileSystem, Log, All);



/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, EditInlineNew)
class HELLAWORLD_API UHellaFileSystem : public UObject, public IReinitializationInterface
{
	GENERATED_BODY()


	UPROPERTY(Instanced)
	UFolder* Root;	

	/** File system will create folders of this class by default  */
	UPROPERTY(EditDefaultsOnly, Category="Filesystem")
	TSubclassOf<UFolder> DefaultFolderClass;

	/** File system will create files of this class by default  */
	UPROPERTY(EditDefaultsOnly, Category = "Filesystem")
	TSubclassOf<UFile> DefaultFileClass;

public:
	UHellaFileSystem();

	/** FileSystem root folder */
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|FileSystem")
	UFolder* GetRoot();

	/** File system will create folders of this class by default  */
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|FileSystem")
	void SetDefaultFolderClass(TSubclassOf<UFolder> NewClass);

	/** File system will create files of this class by default  */
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|FileSystem")
	void SetDefaultFileClass(TSubclassOf<UFile> NewClass);

	/** File system will create folders of this class by default  */
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|FileSystem")
	TSubclassOf<UFolder> GetDefaultFolderClass() const;

	/** File system will create files of this class by default  */
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|FileSystem")
	TSubclassOf<UFile> GetDefaultFileClass() const;




	UFile* CreateFileOfType(FString Path, FString FileName, TSubclassOf<UFile> Type);

	/** Create path and return last folder in path  */
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|FileSystem", meta=(AdvancedDisplay="Type"))
	UFolder* CreatePath(FString Path);


	/** Create file with name and put it using path(creates missing folders in process) */
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|FileSystem")
	UFile* CreateFile(FString Path, FString FileName, UObject* Asset);





	/** Just create file. File must be added manually */
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|FileSystem")
	UFile* CreateFileIsolated(UObject* Asset, FString FileName = TEXT("NewFile")) const;

	/** Just create folder. Folder must be added manually */
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|FileSystem")
	UFolder* CreateFolderIsolated(FString FolderName = TEXT("NewFolder")) const;



	UFUNCTION(BlueprintCallable, Category = "HellaWorld|FileSystem")
	void GetDebugPaths(TArray<FString>& OutPaths) const;


	UFUNCTION(BlueprintCallable, Category = "HellaWorld|FileSystem")
	UHellaFileSystem* GetDuplicate(UObject* NewOuter);

protected:
	//	IReinitializationInterface
	virtual bool Reinitialize_Implementation(const UObject* Template) override;

};
