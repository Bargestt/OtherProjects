// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "ReinitializationInterface.h"
#include "ProjectObject.generated.h"

class UProjectField;


USTRUCT(BlueprintType)
struct FProjectObjectFieldTemplate
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName FieldName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UProjectField> FieldType;
};


USTRUCT(BlueprintType)
struct FProjectObjectTemplate : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ProjectName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FProjectObjectFieldTemplate> Fields;
};

USTRUCT(BlueprintType)
struct FProjectFieldData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FName FieldName;

	UPROPERTY(BlueprintReadOnly)
	TSubclassOf<UProjectField> FieldType;

	UPROPERTY(BlueprintReadOnly)
	UProjectField* Field;
};


/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, Category = "HellaWorld|Project")
class HELLAWORLD_API UProjectObject : public UObject, public IReinitializationInterface
{
	GENERATED_BODY()

private:
	template<typename FieldType, typename T>
	void GetFieldValue(FName FieldName, T& OutValue, bool& OutSuccess) const
	{
		const FieldType* Field = Cast<FieldType>(GetField(FieldName));
		OutSuccess = Field != nullptr;
		if (OutSuccess)
		{
			OutValue = Field->GetValue();
		}
	}

	template<typename FieldType>
	FieldType* CreateField()
	{
		return NewObject<FieldType>((UObject*)this, NAME_None);
	}

	template<typename FieldType, typename T>
	void SetField(FName FieldName, T Value, bool ForceCast)
	{
		UProjectField* Field = GetField(FieldName);

		FieldType* CastedField = Cast<FieldType>(Field);

		if (Field == nullptr || (ForceCast && CastedField == nullptr))
		{
			CastedField = CreateField<FieldType>();
			AddField(FieldName, CastedField);
		}
		CastedField->SetValue(Value);
	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Project")
	FString ProjectName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Project", Instanced)
	TMap<FName, UProjectField*> Fields;	

public:
	FORCEINLINE UProjectField* GetField(FName FieldName);

	FORCEINLINE const UProjectField* GetField(FName FieldName) const;

	/**
	 * Create field of specified class and link it to project
	 * You must add created field to project manually
	 * @param	Project		The Project that this field will be added to
	 * */
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Project", BlueprintPure, meta = (DeterminesOutputType = "Class", DynamicOutputParam = "CreatedField"))
	static void CreateField(UPARAM(ref) UProjectObject*& Project, TSubclassOf<UProjectField> Class, UProjectField*& CreatedField);

	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Project")
	void SetTemplate(const FProjectObjectTemplate& Template);

	/** Make name unique among fields */
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Project")
	FName AdjustName(FName Name) const;
	
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Project")
	void AddField(FName FieldName, UProjectField* Field);

	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Project", BlueprintPure)
	void GetField(FName FieldName, UProjectField*& Field, bool& HasField);

	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Project", BlueprintPure)
	TSubclassOf<UProjectField> GetFieldType(FName FieldName) const;

	/** Remove all fields */
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Project")
	void ClearFields();

	/** Reset all fields to default values */
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Project")
	void ResetFields();

public:

	//////////////////////////////////////////////////////////////////////////
	//	Field operators
	//	
	
	/**
	 * Compare equality of all fields 
	 * @param	StrictCompare	Number of fields must match 
	 */
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Project")
	bool IsEqualTo(const UProjectObject* Other, bool StrictCompare = true) const;

	/** Get fields that equal by type
	 * @param	IgnoreFieldValues	Compare only field types
	 */
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Project")
	TArray<FName> GetEqualFields(const UProjectObject* Other, bool IgnoreFieldValues = false) const;

	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Project", meta = (DeterminesOutputType = "Type", DynamicOutputParam = "OutFields"))
	void GetFieldsOfType(TSubclassOf<UProjectField> Type, TArray<UProjectField*>& OutFields, TArray<FName>& OutNames);


	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Project")
	TArray<FProjectFieldData> GetFields();
	
	//////////////////////////////////////////////////////////////////////////
	//	Getter / Setters


	/** @param	ForceCast	If field is already set but with different value Type, casts field to proper Type	*/
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Project")
	void SetField_AsBool(FName FieldName, bool Value, bool ForceCast = false);

	/** @param	ForceCast	If field is already set but with different value Type, casts field to proper Type	*/
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Project")
	void SetField_AsInt(FName FieldName, int32 Value, bool ForceCast = false);

	/** @param	ForceCast	If field is already set but with different value Type, casts field to proper Type	*/
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Project")
	void SetField_AsFloat(FName FieldName, float Value, bool ForceCast = false);

	/** @param	ForceCast	If field is already set but with different value Type, casts field to proper Type	*/
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Project")
	void SetField_AsVector(FName FieldName, FVector Value, bool ForceCast = false);

	/** @param	ForceCast	If field is already set but with different value Type, casts field to proper Type	*/
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Project")
	void SetField_AsEnum(FName FieldName, uint8 Value, bool ForceCast = false);

	/** @param	ForceCast	If field is already set but with different value Type, casts field to proper Type	*/
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Project")
	void SetField_AsName(FName FieldName, FName Value, bool ForceCast = false);

	/** @param	ForceCast	If field is already set but with different value Type, casts field to proper Type	*/
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Project")
	void SetField_AsString(FName FieldName, FString Value, bool ForceCast = false);

	/** @param	ForceCast	If field is already set but with different value Type, casts field to proper Type	*/
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Project")
	void SetField_AsDateTime(FName FieldName, FDateTime Value, bool ForceCast = false);


	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Project")
	void GetField_AsBool(FName FieldName, bool& Value, bool& Success) const;

	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Project")
	void GetField_AsInt(FName FieldName, int32& Value, bool& Success) const;

	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Project")
	void GetField_AsFloat(FName FieldName, float& Value, bool& Success) const;

	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Project")
	void GetField_AsVector(FName FieldName, FVector& Value, bool& Success) const;

	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Project")
	void GetField_AsEnum(FName FieldName, uint8& Value, bool& Success) const;

	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Project")
	void GetField_AsName(FName FieldName, FName& Value, bool& Success) const;

	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Project")
	void GetField_AsString(FName FieldName, FString& Value, bool& Success) const;

	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Project")
	void GetField_AsDateTime(FName FieldName, FDateTime& Value, bool& Success) const;




protected:

	// IReinitializationInterface
	virtual bool Reinitialize_Implementation(const UObject* Template) override;

};


