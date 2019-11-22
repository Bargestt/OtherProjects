// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "IDetailCustomization.h"


class FHellaFileSystemCustomization : public IDetailCustomization
{
public:

	/** Makes a new instance of this detail layout class for a specific detail view requesting it */
	static TSharedRef<IDetailCustomization> MakeInstance();



	/** IDetailCustomization interface */
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;
};