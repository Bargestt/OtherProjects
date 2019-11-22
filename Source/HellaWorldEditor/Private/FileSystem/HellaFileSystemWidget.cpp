#include "HellaFileSystemWidget.h"
#include "SlateOptMacros.h"

#include "EditorStyleSet.h"
#include "HellaStyle.h"


#include "SPanel.h"
#include "SBoxPanel.h"
#include "SHeaderRow.h"
#include "STreeView.h"
#include "SGridPanel.h"

#include "PropertyEditorModule.h"

#include "ModuleManager.h"
#include "AssetRegistryModule.h"

#include "UICommandList.h"

#include "HellaFileSystem.h"
#include "File.h"
#include "Folder.h"
#include "HellaFileSystemCommands.h"



BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

// ++ This is needed in order to use the localization macro LOCTEXT
#define LOCTEXT_NAMESPACE "SHellaFileSystemWidget"

DEFINE_LOG_CATEGORY(LogHellaFileSystemWidget);



void SHellaFileSystemWidget::Construct(const FArguments& InArgs)
{
	// ++ Asign the argument to our local variable
	// name will be _OwnerHUDArg instead of OwnerHUDArg, see comments about SLATE_ARGUMENT before
	OwnerSystem = InArgs._OwnerSystemArg;

	RebuildTree();

	FHellaFileSystemCommands::Register();	
	BindCommands();

	FMenuBarBuilder MenuBarBuilder(UICommandList);

	
	// Toolbar
	FToolBarBuilder ToolbarBuilder(UICommandList, FMultiBoxCustomization::None);
	ToolbarBuilder.AddToolBarButton(FHellaFileSystemCommands::Get().NewFile, NAME_None, FText::GetEmpty(), LOCTEXT("Button_CreateFile", "Create File"), FSlateIcon(FHellaStyle::GetStyleSetName(), "Hella.CreateFile"));

	ToolbarBuilder.AddToolBarButton(FHellaFileSystemCommands::Get().NewFolder, NAME_None, FText::GetEmpty(), LOCTEXT("Button_CreateFolder", "Create Folder"), FSlateIcon(FHellaStyle::GetStyleSetName(), "Hella.CreateFolder"));
	ToolbarBuilder.AddComboButton(FUIAction(), FOnGetContent::CreateSP(this, &SHellaFileSystemWidget::GetMenuContent, UICommandList));	
	
	ToolbarBuilder.AddToolBarButton(FHellaFileSystemCommands::Get().Delete, NAME_None, FText::GetEmpty(), LOCTEXT("Button_Delete", "Delete File"), FSlateIcon(FHellaStyle::GetStyleSetName(), "Hella.Delete"));
	ToolbarBuilder.AddSeparator();
	ToolbarBuilder.AddToolBarButton(FHellaFileSystemCommands::Get().Copy, NAME_None, FText::GetEmpty(), LOCTEXT("Button_Copy", "Copy File"), FSlateIcon(FHellaStyle::GetStyleSetName(), "Hella.Copy"));
	ToolbarBuilder.AddToolBarButton(FHellaFileSystemCommands::Get().Paste, NAME_None, FText::GetEmpty(), LOCTEXT("Button_Paste", "Paste File"), FSlateIcon(FHellaStyle::GetStyleSetName(), "Hella.Paste"));

	ToolbarBuilder.AddSeparator();
	ToolbarBuilder.AddToolBarButton(FHellaFileSystemCommands::Get().Info, NAME_None, FText::GetEmpty(), LOCTEXT("Button_Info", "Show debug info"), FSlateIcon(FHellaStyle::GetStyleSetName(), "Hella.Info"));

	ToolbarBuilder.AddSeparator();
	ToolbarBuilder.AddWidget(
		SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Center)		
		.WidthOverride(300)
		[			
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Right)
			.AutoWidth()
			[
				SNew(STextBlock)
				.Text(LOCTEXT("File to Copy", "Copied File: "))
				.Font(FCoreStyle::GetDefaultFontStyle("Regular", 11))
			]
			+ SHorizontalBox::Slot()
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Fill)
			[
				SNew(STextBlock)
				.Text(this, &SHellaFileSystemWidget::GetSelectedForCopyFileName)
				.Font(FCoreStyle::GetDefaultFontStyle("Regular", 11))
			]			
		]		
		, NAME_None, false);
	ToolbarBuilder.AddSeparator();

	ToolbarBuilder.AddToolBarButton(FHellaFileSystemCommands::Get().BuildFromFolder, NAME_None, FText::GetEmpty(), LOCTEXT("Button_BuildFromFolder", "Build From Folder"), FSlateIcon(FHellaStyle::GetStyleSetName(), "Hella.Build"));
	ToolbarBuilder.AddSeparator();

	// Selected file editor
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	FDetailsViewArgs DetailsViewArgs(true, false, false, FDetailsViewArgs::HideNameArea, true);
	DetailsViewArgs.NotifyHook = this;
	DetailsPanel = PropertyEditorModule.CreateDetailView(DetailsViewArgs);

	// Layout
	ChildSlot
		.VAlign(VAlign_Fill)
		.HAlign(HAlign_Fill)		
		[
			SNew(SBox)
			.HeightOverride(500)
			[			
				SNew(SVerticalBox)	
				+ SVerticalBox::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Top)
				.Padding(5, 5, 5, 5)
				.AutoHeight()
				[
					ToolbarBuilder.MakeWidget()
				]
				+ SVerticalBox::Slot()
				.VAlign(VAlign_Fill)
				.HAlign(HAlign_Fill)
				[				
					SNew(SSplitter)			
					+ SSplitter::Slot()			
					[				
						SNew(SVerticalBox)
						+ SVerticalBox::Slot()
						.MaxHeight(22)
						[						
							GetHeaderWidget(LOCTEXT("FileSystemView", "View"))
						]
						+ SVerticalBox::Slot()
						.FillHeight(1)					
						[
							SAssignNew(TreeView, SHellaFileTreeView)
							.SelectionMode(ESelectionMode::Single)
							.TreeItemsSource(&Files)
							.OnGenerateRow(this, &SHellaFileSystemWidget::TreeView_OnGenerateRow)
							.OnGetChildren(this, &SHellaFileSystemWidget::TreeView_OnGetChildren)
							.OnSelectionChanged(this, &SHellaFileSystemWidget::TreeView_OnSelectionChange)
						]							
					]
					+ SSplitter::Slot()
					[
						SNew(SVerticalBox)
						+ SVerticalBox::Slot()
						.MaxHeight(22)
						[
							GetHeaderWidget(LOCTEXT("FileSystemSelection", "Selected"))
						]
						+ SVerticalBox::Slot()
						.FillHeight(1)								
						[
							DetailsPanel.ToSharedRef()
						]	
						+ SVerticalBox::Slot()
						.FillHeight(1)
						.VAlign(VAlign_Top)
						.HAlign(HAlign_Center)
						[
							SNew(STextBlock)	
							.Text(LOCTEXT("FileSystemSelectionDetails", "Folder"))
							.Font(FCoreStyle::GetDefaultFontStyle("Bold", 12))
							.Visibility(this, &SHellaFileSystemWidget::ShouldShowFolderView)
						]
					]
				]
			]
		];	
}

TSharedRef<SWidget> SHellaFileSystemWidget::GetHeaderWidget(const FText& Title) const
{
	const FSlateBrush* Border = FEditorStyle::GetBrush("DetailsView.CategoryTop");
	FSlateFontInfo HeaderFont = FCoreStyle::GetDefaultFontStyle("Bold", 9);

	return
		SNew(SBorder)
		.DesiredSizeScale(FVector2D(99, 22))
		.BorderBackgroundColor(FLinearColor(.6, .6, .6, 1.0f))
		.BorderImage(Border)
		[
			SNew(STextBlock)
			.Text(Title)
			.Font(HeaderFont)
		];
}



TSharedRef< SWidget > SHellaFileSystemWidget::GetMenuContent(TSharedPtr<FUICommandList> InCommandList)
{
	FMenuBuilder MenuBuilder(true, InCommandList);

	MenuBuilder.BeginSection("CreatePath", LOCTEXT("CreatePath", "Create Path"));
	{
		MenuBuilder.AddMenuEntry(FHellaFileSystemCommands::Get().AddPath);
		MenuBuilder.AddEditableText(
			LOCTEXT("CreatePath", "Create Path"), 
			LOCTEXT("CreatePathTooltip", "Press Enter to create using string"),
			FSlateIcon(), 
			FText::FromString(Path),
			FOnTextCommitted::CreateSP(this, &SHellaFileSystemWidget::TextChanged)
		);
	}
	MenuBuilder.EndSection();

	return MenuBuilder.MakeWidget();
}

void SHellaFileSystemWidget::NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, UProperty* PropertyThatChanged)
{
	RebuildTree();
}

void SHellaFileSystemWidget::RebuildTree()
{
	Files.Empty();
	if (OwnerSystem.IsValid() && OwnerSystem->GetRoot())
	{
		bool IsDirty = false;
		UPackage* Package = OwnerSystem->GetOutermost();
		if (Package)
		{
			IsDirty = Package->IsDirty();
		}

		if (!OwnerSystem->GetRoot()->UpdateTree())
		{
			// Display message if package was marked dirty because of UpdateTree
			if ( Package && !IsDirty && Package->IsDirty() )
			{
				FText Caption = LOCTEXT("TreeValidationCaption", "Tree was fixed");
				FText Message = LOCTEXT("ShowTreeValidationMesage", "Filesystem had errors. Please save asset to apply fix");

				FMessageDialog::Open(EAppMsgType::Ok, Message, &Caption);				
			}
		}
		TArray<UFSItem*> RootFiles = OwnerSystem->GetRoot()->GetFiles();
		for (UFSItem* File : RootFiles)
		{
			if (File)
			{
				Files.Add(MakeWeakObjectPtr(File));
			}
		}
	}

	if (TreeView.IsValid())
	{
		TreeView->RequestTreeRefresh();
	}
}


TSharedRef<ITableRow> SHellaFileSystemWidget::TreeView_OnGenerateRow(TWeakObjectPtr<UFSItem> Item, const TSharedRef<STableViewBase>& OwnerTable)
{	
	return SNew(STableRow< TWeakObjectPtr<UFSItem> >, OwnerTable)
	[
		SNew(SHellaFileWidget).OwnerFileArg(Item)
	];	
}

void SHellaFileSystemWidget::TreeView_OnGetChildren(TWeakObjectPtr<UFSItem> Item, TArray< TWeakObjectPtr<UFSItem> >& OutChildren)
{
	if (Item.IsValid())
	{
		if (UFolder* Folder = Cast<UFolder>(Item.Get()))
		{
			TArray<UFSItem*> FolderFiles = Folder->GetFiles();
			for (UFSItem* File : FolderFiles)
			{
				if (File) 
				{
					OutChildren.Add(MakeWeakObjectPtr(File));
				}
			}
		}		
	}
}

void SHellaFileSystemWidget::TreeView_OnSelectionChange(TWeakObjectPtr<UFSItem> Item, ESelectInfo::Type SelectionType)
{
	bool bShowDetails = Item.IsValid(); // && Item->GetClass() != UFolder::StaticClass() 
	if (bShowDetails)
	{		
		DetailsPanel->SetObject(Item.Get());
	}
	else
	{
		DetailsPanel->SetObject(nullptr);
	}

	UE_LOG(LogHellaFileSystemWidget, Log, TEXT("Selected %s"), Item.IsValid()? *Item->GetFileName() : TEXT("None"));
}



EVisibility SHellaFileSystemWidget::ShouldShowFolderView() const
{
// Not implemented
// 	TWeakObjectPtr<class UFile> SelectedFile = this->GetSelectedFile();	
// 
// 	if (SelectedFile.IsValid() && SelectedFile->GetClass() == UFolder::StaticClass())
// 	{
// 		return EVisibility::Visible;
// 	}
	return EVisibility::Collapsed;
}

FText SHellaFileSystemWidget::GetSelectedForCopyFileName() const
{
	if (FileToCopy.IsValid())
	{
		return FText::FromString(FileToCopy->GetFileName());
	}
	else
	{
		return LOCTEXT("CopySelected", "None");
	}
}


void SHellaFileSystemWidget::BindCommands()
{
	UICommandList = TSharedPtr<FUICommandList>(new FUICommandList());
	
	UICommandList->MapAction(
		FHellaFileSystemCommands::Get().NewFile,
		FExecuteAction::CreateSP(this, &SHellaFileSystemWidget::Action_NewFile));

	UICommandList->MapAction(
		FHellaFileSystemCommands::Get().NewFolder,
		FExecuteAction::CreateSP(this, &SHellaFileSystemWidget::Action_NewFolder));

	UICommandList->MapAction(
		FHellaFileSystemCommands::Get().Delete,
		FExecuteAction::CreateSP(this, &SHellaFileSystemWidget::Action_DeleteFile));

	UICommandList->MapAction(
		FHellaFileSystemCommands::Get().Copy,
		FExecuteAction::CreateSP(this, &SHellaFileSystemWidget::Action_CopyFile));

	UICommandList->MapAction(
		FHellaFileSystemCommands::Get().Paste,
		FExecuteAction::CreateSP(this, &SHellaFileSystemWidget::Action_PasteFile));

	UICommandList->MapAction(
		FHellaFileSystemCommands::Get().BuildFromFolder,
		FExecuteAction::CreateSP(this, &SHellaFileSystemWidget::Action_BuildFromFolder));

	UICommandList->MapAction(
		FHellaFileSystemCommands::Get().AddPath,
		FExecuteAction::CreateSP(this, &SHellaFileSystemWidget::Action_AddPath));

	UICommandList->MapAction(
		FHellaFileSystemCommands::Get().Info,
		FExecuteAction::CreateSP(this, &SHellaFileSystemWidget::Action_ShowInfo));
}




TWeakObjectPtr<class UFSItem> SHellaFileSystemWidget::GetSelectedFile() const
{
	if (OwnerSystem.IsValid() && TreeView.IsValid())
	{
		TArray<TWeakObjectPtr<class UFSItem>> Files = TreeView->GetSelectedItems();
		if (Files.Num() == 1)
		{
			return Files[0];
		}
	}
	return TWeakObjectPtr<class UFSItem>(nullptr);
}

UFolder* SHellaFileSystemWidget::GetCurrentFolder() const
{
	if (!OwnerSystem.IsValid()) return nullptr;

	TWeakObjectPtr<class UFSItem> SelectedFile = GetSelectedFile();

	UFolder* Folder = nullptr;
	if (SelectedFile.IsValid())
	{
		if (SelectedFile->IsA<UFolder>())
		{
			Folder = Cast<UFolder>(SelectedFile.Get());		
		}
		else
		{
			Folder = SelectedFile->GetParent();
		}
	}
	else
	{
		Folder = OwnerSystem->GetRoot();
	}

	return Folder;
}

void SHellaFileSystemWidget::Action_CopyFile()
{
	UE_LOG(LogHellaFileSystemWidget, Log, TEXT("Action: CopyFile"));

	TWeakObjectPtr<class UFSItem> SelectedFile = GetSelectedFile();
	if (SelectedFile.IsValid())
	{
		FileToCopy = SelectedFile;
	}
}

void SHellaFileSystemWidget::Action_PasteFile()
{
	UE_LOG(LogHellaFileSystemWidget, Log, TEXT("Action: PasteFile"));

	UFolder* Folder = GetCurrentFolder();
	if (Folder)
	{
		UFSItem* NewFile = FileToCopy->Duplicate();
		Folder->AddFile(NewFile);

		OwnerSystem->MarkPackageDirty();
		UE_LOG(LogHellaFileSystemWidget, Log, TEXT("Copied %s to folder %s"), NewFile ? *NewFile->GetFileName() : TEXT("None"), *Folder->GetFileName());
		RebuildTree();
	}
	
}

void SHellaFileSystemWidget::Action_NewFile()
{
	UE_LOG(LogHellaFileSystemWidget, Log, TEXT("Action: NewFile"));
	
	UFolder* Folder = GetCurrentFolder();
	if (Folder && OwnerSystem.IsValid())
	{		
		UFSItem* NewFile = OwnerSystem->CreateFileIsolated(nullptr);
		Folder->AddFile(NewFile);

		OwnerSystem->MarkPackageDirty();
		RebuildTree();
	}
}

void SHellaFileSystemWidget::Action_NewFolder()
{
	UE_LOG(LogHellaFileSystemWidget, Log, TEXT("Action: NewFolder"));
	
	UFolder* Folder = GetCurrentFolder();
	if (Folder && OwnerSystem.IsValid())
	{
		UFSItem* NewFile = OwnerSystem->CreateFolderIsolated();
		Folder->AddFile(NewFile);

		OwnerSystem->MarkPackageDirty();
		RebuildTree();
	}
}

void SHellaFileSystemWidget::Action_DeleteFile()
{
	UE_LOG(LogHellaFileSystemWidget, Log, TEXT("Action: DeleteFile"));
	TWeakObjectPtr<class UFSItem> SelectedFile = GetSelectedFile();
	if (SelectedFile.IsValid())
	{
		if (SelectedFile.Get() == OwnerSystem->GetRoot()) return;

		SelectedFile->Delete();

		OwnerSystem->MarkPackageDirty();
		RebuildTree();
	}
}


void SHellaFileSystemWidget::Action_BuildFromFolder()
{
	UE_LOG(LogHellaFileSystemWidget, Log, TEXT("Action: BuildFromFolder"));

	if (!OwnerSystem.IsValid()) return;

	FText Caption = LOCTEXT("BuildFromFolderCaption", "Build From Folder");
	FText Message = FText::Format(LOCTEXT("BuildFromFolderCaptionMessage", "This action will build a hierarchy using folder '{0}' \nAll previously built hierarchy will be lost!"), FText::FromString(OwnerSystem->GetName()));
	if (FMessageDialog::Open(EAppMsgType::YesNo, Message, &Caption) != EAppReturnType::Yes)
	{
		UE_LOG(LogHellaFileSystemWidget, Log, TEXT("BuildFromFolder was Cancelled "));
		return;
	}
	UE_LOG(LogHellaFileSystemWidget, Log, TEXT("Building from folder"));	



	FString SystemPath = FPaths::GetPath(OwnerSystem->GetPathName());
	FString SystemName = FPaths::GetBaseFilename(OwnerSystem->GetPathName());
	FString AssetsFolder = FPaths::Combine(SystemPath, SystemName);

	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	TArray<FAssetData> AssetData;
	AssetRegistryModule.Get().GetAssetsByPath(FName(*AssetsFolder), AssetData, true);

	UE_LOG(LogHellaFileSystemWidget, Log, TEXT("%d Assets in %s"), AssetData.Num(), *AssetsFolder);

	OwnerSystem->GetRoot()->DeleteAllFiles();
	for (const FAssetData& Asset : AssetData)
	{
		FString AssetPath = FPaths::GetPath(Asset.ObjectPath.ToString());
		AssetPath.RemoveFromStart(AssetsFolder, ESearchCase::CaseSensitive);

		UE_LOG(LogHellaFileSystemWidget, Log, TEXT("Creating '%s' \"%s\""), *Asset.AssetClass.ToString(), *(AssetPath / Asset.AssetName.ToString()));

		OwnerSystem->CreateFile(AssetPath, Asset.AssetName.ToString(), Asset.GetAsset());
	}
	OwnerSystem->MarkPackageDirty();
	RebuildTree();
}




void SHellaFileSystemWidget::Action_AddPath()
{
	UE_LOG(LogHellaFileSystemWidget, Log, TEXT("Action: AddPath"));

	if (!OwnerSystem.IsValid()) return;

	OwnerSystem->CreatePath(Path);

	OwnerSystem->MarkPackageDirty();
	RebuildTree();
}

void SHellaFileSystemWidget::Action_ShowInfo()
{
	UE_LOG(LogHellaFileSystemWidget, Log, TEXT("Action: Info"));

	if (!OwnerSystem.IsValid()) return;

	TArray<FString> Paths;
	OwnerSystem->GetDebugPaths(Paths);

	FString PathsCombined = FString::Join(Paths, TEXT("\n"));

	FText Caption = LOCTEXT("ShowInfoCaption", "Debug paths info");
	FText Message = FText::Format(LOCTEXT("ShowInfoMesage", "'{0}'"), FText::FromString(PathsCombined));
	
	FMessageDialog::Open(EAppMsgType::Ok, Message, &Caption);
}

void SHellaFileSystemWidget::TextChanged(const FText& Text, ETextCommit::Type Type)
{
	Path = Text.ToString();
	if (Type == ETextCommit::OnEnter) 
	{
		Action_AddPath();
	}
}

//////////////////////////////////////////////////////////////////////////
//	File widget

void SHellaFileWidget::Construct(const FArguments& InArgs)
{
	OwnerFile = InArgs._OwnerFileArg;

	ChildSlot
	[
		SNew(STextBlock)
		.Text(this, &SHellaFileWidget::GetFileName)	
		.Font(FCoreStyle::GetDefaultFontStyle("Regular", FCoreStyle::RegularTextSize))
	];
}

FText SHellaFileWidget::GetFileName() const
{
	if (OwnerFile.IsValid())
	{
		return FText::FromString(OwnerFile->GetFileName());
	}
	else
	{
		return LOCTEXT("TreeItem", "Invalid item. Wtf?");
	}
}

// ++ We need to undefine this namespace after we finish creating the Slate widget
#undef LOCTEXT_NAMESPACE

END_SLATE_FUNCTION_BUILD_OPTIMIZATION