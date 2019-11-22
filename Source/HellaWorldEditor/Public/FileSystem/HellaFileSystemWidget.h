// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class UHellaFileSystem;
class UFSItem;
class SHellaFileEditWidget;
class SEditableText;
class IDetailsView;
class FUICommandList;
class UFolder;

DECLARE_LOG_CATEGORY_EXTERN(LogHellaFileSystemWidget, Log, All);

typedef STreeView< TWeakObjectPtr<UFSItem> > SHellaFileTreeView;


class HELLAWORLDEDITOR_API SHellaFileSystemWidget : public SCompoundWidget, public FNotifyHook
{
public:
	SLATE_BEGIN_ARGS(SHellaFileSystemWidget)
	{}

	SLATE_ARGUMENT(TWeakObjectPtr<class UHellaFileSystem>, OwnerSystemArg);

	SLATE_END_ARGS()



	// Constructs this widget with InArgs. Needed for every widget. Builds this widget and any of it's children
	void Construct(const FArguments& InArgs);

private:
	// Widget construction
	TSharedRef<SWidget> GetHeaderWidget(const FText& Title) const;

	TSharedRef<SWidget> GetMenuContent(TSharedPtr<FUICommandList> InCommandList);

	// FNotifyHook
	virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, UProperty* PropertyThatChanged) override;

	//Tree View
	void RebuildTree();

	TSharedRef<ITableRow> TreeView_OnGenerateRow(TWeakObjectPtr<UFSItem> Item, const TSharedRef<STableViewBase>& OwnerTable);

	void TreeView_OnGetChildren(TWeakObjectPtr<UFSItem> Item, TArray< TWeakObjectPtr<UFSItem> >& OutChildren);

	void TreeView_OnSelectionChange(TWeakObjectPtr<UFSItem> Item, ESelectInfo::Type SelectionType);

	EVisibility ShouldShowFolderView() const;

	FText GetSelectedForCopyFileName() const;

	// Toolbar
	TSharedPtr<FUICommandList> UICommandList;

	void BindCommands();

	TWeakObjectPtr<class UFSItem> GetSelectedFile() const;

	UFolder* GetCurrentFolder() const;

	// TODO: Decouple
	void Action_CopyFile();
	void Action_PasteFile();
	void Action_NewFile();
	void Action_NewFolder();
	void Action_DeleteFile();
	void Action_BuildFromFolder();

	void Action_AddPath();

	void Action_ShowInfo();

	FString Path;
	void TextChanged(const FText& TExt, ETextCommit::Type Type);



	TWeakObjectPtr<class UHellaFileSystem> OwnerSystem;

	TSharedPtr<SHellaFileTreeView> TreeView;

	TArray<TWeakObjectPtr<UFSItem>> Files;


	TSharedPtr<class IDetailsView> DetailsPanel;


	TWeakObjectPtr<class UFSItem> FileToCopy;

	TSharedPtr<SEditableTextBox> PathInput;
};


class HELLAWORLDEDITOR_API SHellaFileWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SHellaFileWidget)
	{}

	SLATE_ARGUMENT(TWeakObjectPtr<class UFSItem>, OwnerFileArg);

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	FText GetFileName() const;

private:

	TWeakObjectPtr<class UFSItem> OwnerFile;
};





