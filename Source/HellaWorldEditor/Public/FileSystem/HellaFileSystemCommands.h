// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"


class FHellaFileSystemCommands : public TCommands<FHellaFileSystemCommands>
{
public:
	FHellaFileSystemCommands() : TCommands<FHellaFileSystemCommands>("HellaFileSystemWidgetCommands", NSLOCTEXT("HellaFileSystem", "CommandsName", "File Operations"), NAME_None, FEditorStyle::GetStyleSetName()) {}

	/** Initialize commands */
	virtual void RegisterCommands() override;

public:
	TSharedPtr<FUICommandInfo> NewFile;
	TSharedPtr<FUICommandInfo> NewFolder;
	TSharedPtr<FUICommandInfo> Delete;
	TSharedPtr<FUICommandInfo> Copy;
	TSharedPtr<FUICommandInfo> Paste;

	TSharedPtr<FUICommandInfo> BuildFromFolder;

	TSharedPtr<FUICommandInfo> AddPath;

	TSharedPtr<FUICommandInfo> Info;


	TArray<TSharedPtr<FUICommandInfo>> Commands;
};






