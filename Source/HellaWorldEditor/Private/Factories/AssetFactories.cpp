// Fill out your copyright notice in the Description page of Project Settings.

#include "ClassViewerModule.h"
#include "ClassViewerFilter.h"
#include "SClassPickerDialog.h"

#include "HellaWorldEditorModule.h"

#include "ProjectObjectFactory.h"
#include "HellaFileSystemFactory.h"
#include "HellaOSStyleFactory.h"

#include "ProjectObject.h"
#include "HellaFileSystem.h"
#include "HellaOSStyle.h"


/**
 * 
 *	Aggregated factories to share FAssetClassParentFilter or anything that might be required later
 * 
 * 
 * 
 */


 // TODO: Make asset actions and remove module load in category bit getter




/*--------------------------------------------
 	Shared
 *--------------------------------------------*/


class FAssetClassParentFilter : public IClassViewerFilter
{
public:
	FAssetClassParentFilter() : DisallowedClassFlags(CLASS_None) {}

	/** All children of these classes will be included unless filtered out by another setting. */
	TSet< const UClass* > AllowedChildrenOfClasses;

	/** Disallowed class flags. */
	EClassFlags DisallowedClassFlags;

	virtual bool IsClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const UClass* InClass, TSharedRef< FClassViewerFilterFuncs > InFilterFuncs) override
	{
		return !InClass->HasAnyClassFlags(DisallowedClassFlags)
			&& InFilterFuncs->IfInChildOfClassesSet(AllowedChildrenOfClasses, InClass) != EFilterReturn::Failed;
	}

	virtual bool IsUnloadedClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const TSharedRef< const IUnloadedBlueprintData > InUnloadedClassData, TSharedRef< FClassViewerFilterFuncs > InFilterFuncs) override
	{
		return !InUnloadedClassData->HasAnyClassFlags(DisallowedClassFlags)
			&& InFilterFuncs->IfInChildOfClassesSet(AllowedChildrenOfClasses, InUnloadedClassData) != EFilterReturn::Failed;
	}
};


/*--------------------------------------------
 	UProjectObjectFactory
 *--------------------------------------------*/

UProjectObjectFactory::UProjectObjectFactory()
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UProjectObject::StaticClass();
}

UObject* UProjectObjectFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	if (ProjectObjectClass)
	{
		return NewObject<UProjectObject>(InParent, ProjectObjectClass, Name, Flags);
	}
	else
	{
		check(Class->IsChildOf(UProjectObject::StaticClass()));
		return NewObject<UProjectObject>(InParent, Class, Name, Flags);
	}
}

bool UProjectObjectFactory::ShouldShowInNewMenu() const
{
	return true;
}

uint32 UProjectObjectFactory::GetMenuCategories() const
{
	FHellaWorldEditorModule& HellaModule = FModuleManager::LoadModuleChecked<FHellaWorldEditorModule>("HellaWorldEditor");
	return HellaModule.GetAssetCategoryBit();
}

bool UProjectObjectFactory::ConfigureProperties()
{
	// nullptr the DataAssetClass so we can check for selection
	ProjectObjectClass = nullptr;

	// Load the classviewer module to display a class picker
	FClassViewerModule& ClassViewerModule = FModuleManager::LoadModuleChecked<FClassViewerModule>("ClassViewer");

	// Fill in options
	FClassViewerInitializationOptions Options;
	Options.Mode = EClassViewerMode::ClassPicker;

	TSharedPtr<FAssetClassParentFilter> Filter = MakeShareable(new FAssetClassParentFilter);
	Options.ClassFilter = Filter;

	Filter->DisallowedClassFlags = CLASS_Abstract | CLASS_Deprecated | CLASS_NewerVersionExists | CLASS_HideDropDown;
	Filter->AllowedChildrenOfClasses.Add(UProjectObject::StaticClass());

	const FText TitleText = NSLOCTEXT("HellaWorldEditor", "CreateProjectObjectOptions", "Pick Project Object Class");
	UClass* ChosenClass = nullptr;
	const bool bPressedOk = SClassPickerDialog::PickClass(TitleText, Options, ChosenClass, UProjectObject::StaticClass());

	if (bPressedOk)
	{
		ProjectObjectClass = ChosenClass;
	}

	return bPressedOk;
}



/*--------------------------------------------
 	UHellaFileSystemFactory
 *--------------------------------------------*/


UHellaFileSystemFactory::UHellaFileSystemFactory()
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UHellaFileSystem::StaticClass();
}

UObject* UHellaFileSystemFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	check(Class->IsChildOf(UHellaFileSystem::StaticClass()));
	return NewObject<UHellaFileSystem>(InParent, Class, Name, Flags);
}

bool UHellaFileSystemFactory::ShouldShowInNewMenu() const
{
	return true;
}

uint32 UHellaFileSystemFactory::GetMenuCategories() const
{
	FHellaWorldEditorModule& HellaModule = FModuleManager::LoadModuleChecked<FHellaWorldEditorModule>("HellaWorldEditor");
	return HellaModule.GetAssetCategoryBit();
}

/*--------------------------------------------
 	UHellaOSStyleFactory
 *--------------------------------------------*/

UHellaOSStyleFactory::UHellaOSStyleFactory()
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UHellaOSStyle::StaticClass();
}

UObject* UHellaOSStyleFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	check(Class->IsChildOf(UHellaOSStyle::StaticClass()));
	return NewObject<UHellaOSStyle>(InParent, Class, Name, Flags);
}

bool UHellaOSStyleFactory::ShouldShowInNewMenu() const
{
	return true;
}

uint32 UHellaOSStyleFactory::GetMenuCategories() const
{
	FHellaWorldEditorModule& HellaModule = FModuleManager::LoadModuleChecked<FHellaWorldEditorModule>("HellaWorldEditor");
	return HellaModule.GetAssetCategoryBit();
}	




