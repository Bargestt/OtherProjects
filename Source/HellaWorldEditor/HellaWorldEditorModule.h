// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Engine.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"
#include "UnrealEd.h"
#include "AssetTypeCategories.h"

DECLARE_LOG_CATEGORY_EXTERN(HellaWorldEditor, All, All)

class FHellaWorldEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;


	EAssetTypeCategories::Type GetAssetCategoryBit() const { return AssetCategoryBit; }
protected:
	EAssetTypeCategories::Type AssetCategoryBit;
};