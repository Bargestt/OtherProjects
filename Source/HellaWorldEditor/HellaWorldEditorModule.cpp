// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "HellaWorldEditorModule.h"

#include "Modules/ModuleManager.h"
#include "Modules/ModuleInterface.h"
#include "PropertyEditorModule.h"

#include "AssetToolsModule.h"

#include "HellaStyle.h"

#include "HellaFileSystemCustomization.h"

#include "HellaFileSystem.h"
#include "ProjectTask.h"


IMPLEMENT_GAME_MODULE(FHellaWorldEditorModule, HellaWorldEditor);

DEFINE_LOG_CATEGORY(HellaWorldEditor)

#define LOCTEXT_NAMESPACE "HellaWorldEditor"

void FHellaWorldEditorModule::StartupModule()
{
	UE_LOG(HellaWorldEditor, Warning, TEXT("HellaWorldEditor: Log Started"));


	// Register asset types
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	// register AI category so that AI assets can register to it
	AssetCategoryBit = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("HellaWorld")), LOCTEXT("HellaWorldAssetCategory", "Hella World"));
	

	FHellaStyle::Initialize();

	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	
	//Custom detail views
	PropertyModule.RegisterCustomClassLayout(UHellaFileSystem::StaticClass()->GetFName(), FOnGetDetailCustomizationInstance::CreateStatic(&FHellaFileSystemCustomization::MakeInstance));

	PropertyModule.NotifyCustomizationModuleChanged();
}

void FHellaWorldEditorModule::ShutdownModule()
{
	UE_LOG(HellaWorldEditor, Warning, TEXT("HellaWorldEditor: Log Ended"));

	FHellaStyle::Shutdown();

	if (FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
	{
		FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
		PropertyModule.UnregisterCustomClassLayout(UHellaFileSystem::StaticClass()->GetFName());
		PropertyModule.UnregisterCustomClassLayout(UProjectTask::StaticClass()->GetFName());
	}
}

#undef LOCTEXT_NAMESPACE