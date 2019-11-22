// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "ProjectObjectFactory.generated.h"

class UProjectObject;

/**
 * 
 */
UCLASS()
class HELLAWORLDEDITOR_API UProjectObjectFactory : public UFactory
{
	GENERATED_BODY()

	UProjectObjectFactory();

	UPROPERTY(EditAnywhere, Category = ProjectObject)
	TSubclassOf<UProjectObject> ProjectObjectClass;
	
	// UFactory Interface
	virtual bool ConfigureProperties() override;
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	virtual bool ShouldShowInNewMenu() const override;
	virtual uint32 GetMenuCategories() const override;
	// End of UFactory interface
	



};
