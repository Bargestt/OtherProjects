// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "HellaStyle.h"

#include "HellaWorldEditorModule.h"
#include "SlateGameResources.h" 

#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush( RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define BOX_BRUSH( RelativePath, ... ) FSlateBoxBrush( RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define BORDER_BRUSH( RelativePath, ... ) FSlateBorderBrush( RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define DEFAULT_FONT(...) FCoreStyle::GetDefaultFontStyle(__VA_ARGS__)
#define ICON_FONT(...) FSlateFontInfo(RootToContentDir("Fonts/FontAwesome", TEXT(".ttf")), __VA_ARGS__)


TSharedPtr<FSlateStyleSet> FHellaStyle::HellaWorldEditorStyleInstance = NULL;

void FHellaStyle::Initialize()
{
	if (!HellaWorldEditorStyleInstance.IsValid())
	{
		HellaWorldEditorStyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*HellaWorldEditorStyleInstance);
	}
}

void FHellaStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*HellaWorldEditorStyleInstance);
	ensure(HellaWorldEditorStyleInstance.IsUnique());
	HellaWorldEditorStyleInstance.Reset();
}

FName FHellaStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("HellaStyle"));
	return StyleSetName;
}

TSharedRef<FSlateStyleSet> FHellaStyle::Create()
{
	TSharedRef< class FHellaStyle::FStyle > StyleRef = MakeShareable(new FHellaStyle::FStyle());
	//TSharedRef<FSlateStyleSet> StyleRef = FSlateGameResources::New(FHellaWorldEditorStyle::GetStyleSetName(), "/Game/UI/Styles", "/Game/UI/Styles");
	StyleRef->Initialize();
	return StyleRef;
}

const ISlateStyle& FHellaStyle::Get()
{
	return *HellaWorldEditorStyleInstance;
}

FHellaStyle::FStyle::FStyle()
	: FSlateStyleSet(FHellaStyle::GetStyleSetName())

	, Icon7x16(7.0f, 16.0f)
	, Icon8x4(8.0f, 4.0f)
	, Icon16x4(16.0f, 4.0f)
	, Icon8x8(8.0f, 8.0f)
	, Icon10x10(10.0f, 10.0f)
	, Icon12x12(12.0f, 12.0f)
	, Icon12x16(12.0f, 16.0f)
	, Icon14x14(14.0f, 14.0f)
	, Icon16x16(16.0f, 16.0f)
	, Icon16x20(16.0f, 20.0f)
	, Icon20x20(20.0f, 20.0f)
	, Icon22x22(22.0f, 22.0f)
	, Icon24x24(24.0f, 24.0f)
	, Icon25x25(25.0f, 25.0f)
	, Icon32x32(32.0f, 32.0f)
	, Icon40x40(40.0f, 40.0f)
	, Icon48x48(48.0f, 48.0f)
	, Icon64x64(64.0f, 64.0f)
	, Icon36x24(36.0f, 24.0f)
	, Icon128x128(128.0f, 128.0f)
{
		
}

void FHellaStyle::FStyle::Initialize()
{
	SetContentRoot(FPaths::EngineContentDir() / TEXT("Editor/Slate"));
	SetCoreContentRoot(FPaths::EngineContentDir() / TEXT("Slate"));

	Set("Hella.CreateFolder", new IMAGE_BRUSH("/Icons/icon_CurveEditor_Create_40x", Icon40x40));
	Set("Hella.CreateFile", new IMAGE_BRUSH("Icons/icon_add_40x", Icon40x40));
	Set("Hella.Delete", new IMAGE_BRUSH("/Icons/icon_Cascade_DeleteLOD_40x", Icon40x40));
	Set("Hella.Copy", new IMAGE_BRUSH("/Icons/Edit/icon_Edit_Copy_40x", Icon40x40));
	Set("Hella.Paste", new IMAGE_BRUSH("/Icons/Edit/icon_Edit_Paste_40x", Icon40x40));

	Set("Hella.Build", new IMAGE_BRUSH("/Icons/icon_build_40x", Icon40x40));
	Set("Hella.Info", new IMAGE_BRUSH("/Icons/AssetIcons/Note_64x", Icon40x40));

	Set("ClassIcon.HellaFileSystem", new IMAGE_BRUSH("Icons/VREditor/T_Radial_Windows", Icon16x16));
	Set("ClassThumbnail.HellaFileSystem", new IMAGE_BRUSH("Icons/VREditor/T_Radial_Windows", Icon64x64));

	
	Set("ClassIcon.ProjectObject", new IMAGE_BRUSH("Icons/icon_Blueprint_Options_512px", Icon16x16));
	Set("ClassThumbnail.ProjectObject", new IMAGE_BRUSH("Icons/icon_Blueprint_Options_512px", Icon64x64));

	//No need
	//Set("ClassIcon.ProjectObject", new IMAGE_BRUSH("Icons/icon_Blueprint_Options_512px", Icon16x16));
	//Set("ClassThumbnail.ProjectObject_Blueprint_C", new IMAGE_BRUSH("Icons/icon_Blueprint_Options_512px", Icon64x64));

	Set("ClassIcon.ProjectField_Bool", new IMAGE_BRUSH("Icons/pill_16x", Icon16x16,			FLinearColor(0.300000f, 0.0f, 0.0f, 1.0f)));
	Set("ClassIcon.ProjectField_Class", new IMAGE_BRUSH("Icons/pill_16x", Icon16x16,		FLinearColor(0.1f, 0.0f, 0.5f, 1.0f)));
	Set("ClassIcon.ProjectField_Enum", new IMAGE_BRUSH("Icons/pill_16x", Icon16x16,			FLinearColor(0.0f, 0.160000f, 0.131270f, 1.0f)));
	Set("ClassIcon.ProjectField_Float", new IMAGE_BRUSH("Icons/pill_16x", Icon16x16,		FLinearColor(0.357667f, 1.0f, 0.060000f, 1.0f)));
	Set("ClassIcon.ProjectField_Int", new IMAGE_BRUSH("Icons/pill_16x", Icon16x16,			FLinearColor(0.013575f, 0.770000f, 0.429609f, 1.0f)));
	Set("ClassIcon.ProjectField_Name", new IMAGE_BRUSH("Icons/pill_16x", Icon16x16,			FLinearColor(0.607717f, 0.224984f, 1.0f, 1.0f)));
	Set("ClassIcon.ProjectField_NativeEnum", new IMAGE_BRUSH("Icons/pill_16x", Icon16x16,	FLinearColor(0.0f, 0.160000f, 0.131270f, 1.0f)));
	Set("ClassIcon.ProjectField_Object", new IMAGE_BRUSH("Icons/pill_16x", Icon16x16,		FLinearColor(0.0f, 0.4f, 0.910000f, 1.0f)));
	Set("ClassIcon.ProjectField_Rotator", new IMAGE_BRUSH("Icons/pill_16x", Icon16x16,		FLinearColor(0.353393f, 0.454175f, 1.0f, 1.0f)));
	Set("ClassIcon.ProjectField_String", new IMAGE_BRUSH("Icons/pill_16x", Icon16x16,		FLinearColor(1.0f, 0.0f, 0.660537f, 1.0f)));
	Set("ClassIcon.ProjectField_Vector", new IMAGE_BRUSH("Icons/pill_16x", Icon16x16,		FLinearColor(1.0f, 0.591255f, 0.016512f, 1.0f)));
	Set("ClassIcon.ProjectField_DateTime", new IMAGE_BRUSH("Icons/pill_16x", Icon16x16,		FLinearColor(0.0f, 0.0f, 0.16f, 1.0f)));



	Set("ClassIcon.HellaOSStyle", new IMAGE_BRUSH("UMG/Palette_40x", Icon16x16));
	Set("ClassThumbnail.HellaOSStyle", new IMAGE_BRUSH("UMG/Palette_40x", Icon64x64));

	Set("ClassIcon.ProjectTask", new IMAGE_BRUSH("Icons/AssetIcons/EnvQuery_64x", Icon16x16));
	Set("ClassThumbnail.ProjectTask", new IMAGE_BRUSH("Icons/AssetIcons/EnvQuery_64x", Icon64x64));

	Set("ClassIcon.ProjectTaskGenerator", new IMAGE_BRUSH("Icons/icon_GenericCommand_40x", Icon16x16));
	Set("ClassThumbnail.ProjectTaskGenerator", new IMAGE_BRUSH("Icons/icon_GenericCommand_40x", Icon64x64));
}
