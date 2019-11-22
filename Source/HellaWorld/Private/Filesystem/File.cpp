// Fill out your copyright notice in the Description page of Project Settings.

#include "File.h"
#include "SlateImageBrush.h"
#include "ProjectObject.h"






bool UFile::IsSupportedAsset(UObject* TestAsset)
{
	bool IsSupported = TestAsset->IsA<UTexture2D>() || TestAsset->IsA<UProjectObject>();
	return IsSupported;
}

void UFile::SetAsset(UObject* NewAsset)
{
	if (IsSupportedAsset(NewAsset))
	{
		Asset = NewAsset;
	}
	else
	{
		Asset = nullptr;
	}
}

UFile* UFile::SetAssetInline(UFile*& File, UObject* NewAsset)
{
	if (File)
	{
		File->SetAsset(NewAsset);
	}
	return File;
}

UObject* UFile::GetAsset() const
{
	return Asset;
}

FName UFile::GetObjectStyle_Implementation() const
{
	FString AssetStyle;

	if (Asset && Asset->GetClass())
	{
		AssetStyle = Asset->GetClass()->GetName();
		AssetStyle.RemoveFromEnd(TEXT("_C"));
	}
	else
	{
		AssetStyle = TEXT("Default");
	}
	return *(TEXT("File.") + AssetStyle);
}

bool UFile::UseCustomBrush_Implementation() const
{
	return Asset ? Asset->IsA<UTexture2D>() : false;
}

FSlateBrush UFile::GetCustomBrush_Implementation()
{
	FSlateBrush Brush;
	Brush.ImageSize = FVector2D(64, 64);
	Brush.DrawAs = ESlateBrushDrawType::Image;

	UTexture2D* Texture = Cast<UTexture2D>(Asset);
	Brush.SetResourceObject(Texture);

	return Brush;
}

void UFile::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	TagContainer = Tags;
}

