// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagAssetInterface.h"
#include "StylizedObjectInterface.h"
#include "FSItem.h"
#include "File.generated.h"

/**
 * Basic file with data
 */
UCLASS(Blueprintable)
class HELLAWORLD_API UFile : public UFSItem, public IGameplayTagAssetInterface, public IStylizedObjectInterface
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "File", meta=(AllowPrivateAccess = true, AllowedClasses = "Texture2D,ProjectObject", ExactClass = false))
	UObject* Asset;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tags")
	FGameplayTagContainer Tags;


public:
	/** invalid pointers will return false but can be used in assets */
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|FileSystem|File")
	static bool IsSupportedAsset(UObject* TestAsset);

	UFUNCTION(BlueprintCallable, Category = "HellaWorld|FileSystem|File")
	void SetAsset(UObject* NewAsset);

	/** Pure function for convenience */
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|FileSystem|File", BlueprintPure)
	static UFile* SetAssetInline(UPARAM(ref) UFile*& File, UObject* NewAsset);

	UFUNCTION(BlueprintCallable, Category = "HellaWorld|FileSystem|File")
	UObject* GetAsset() const;



	// IStylizedObjectInterface
	virtual FName GetObjectStyle_Implementation() const override;

	virtual bool UseCustomBrush_Implementation() const override;

	virtual FSlateBrush GetCustomBrush_Implementation() override;


private:

	// IGameplayTagAssetInterface
	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;

};
