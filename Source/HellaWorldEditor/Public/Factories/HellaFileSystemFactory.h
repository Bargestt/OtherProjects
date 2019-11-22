// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "HellaFileSystemFactory.generated.h"

/**
 * 
 */
UCLASS()
class HELLAWORLDEDITOR_API UHellaFileSystemFactory : public UFactory
{
	GENERATED_BODY()
	
	
	UHellaFileSystemFactory();

	// UFactory Interface
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	virtual bool ShouldShowInNewMenu() const override;
	virtual uint32 GetMenuCategories() const override;
	// End of UFactory interface

	
};
