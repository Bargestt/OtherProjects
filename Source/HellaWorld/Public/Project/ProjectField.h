// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectField.generated.h"

class UProjectObject;

UENUM(BlueprintType)
enum class EFieldType : uint8
{
	Undefined,
	Bool,
	Int,
	Float,
	Vector,
	Enum,
	Name,
	String,
	DateTime
};


UCLASS(Abstract, BlueprintType, Blueprintable, Category="HellaWorld|Project", EditInlineNew, CollapseCategories, AutoExpandCategories = (ProjectField))
class HELLAWORLD_API UProjectField : public UObject
{
	GENERATED_BODY()

protected:
	bool bIsEmpty = true;

public:

	UFUNCTION(BlueprintCallable, Category="HellaWorld|Project|Field")
	virtual FString ToString() const { return TEXT(""); }

	// returns true If value wasn't set yet 
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Project|Field")
	virtual bool IsEmpty() const { return bIsEmpty; }

	// Reset to default value and make empty
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Project|Field")
	void Reset() 
	{
		ResetImpl();
		bIsEmpty = true;
	}
protected:
	virtual void ResetImpl() {}

public:

	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Project|Field")
	virtual EFieldType GetDataType() const { return EFieldType::Undefined; }

	// Compare field type and value
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Project|Field")
	virtual bool IsEqual(const UProjectField* Other) const { return false; }

	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Project|Field")
	bool IsSameDataType(const UProjectField* Other) const { return Other && Other->GetDataType() == GetDataType(); }

protected:

	//	Template version with type inferring to reduce copy paste
	template<typename BaseType>
	FORCEINLINE static bool CompareImpl(const BaseType* A, const UProjectField* B)
	{ 
		const BaseType* CastedB = Cast<BaseType>(B);
		return A && CastedB && A->GetValue() == CastedB->GetValue();
	}

	// Again for reducing copy paste and to centralize on base class
	template<typename ValueType>
	FORCEINLINE void SetValueByRef(ValueType& ValueFieldRef, ValueType NewValue)
	{
		ValueFieldRef = NewValue;
		bIsEmpty = false;
	}
	   

};


UCLASS()
class HELLAWORLD_API UProjectField_Bool : public UProjectField
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditInstanceOnly, meta=(ExposeOnSpawn), BlueprintReadOnly)
	bool Value;

public:
	virtual FString ToString() const override { return Value ? TEXT("true") : TEXT("false"); }

	virtual EFieldType GetDataType() const override { return EFieldType::Bool; }

	virtual bool IsEqual(const UProjectField* Other) const override { return CompareImpl(this, Other); }


	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Project|Field")
	void SetValue(bool NewValue) { 	SetValueByRef(Value, NewValue);	}

	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Project|Field")
	bool GetValue() const {return Value; }

protected:
	virtual void ResetImpl() override {	Value = false; }
};

UCLASS()
class HELLAWORLD_API UProjectField_Int : public UProjectField
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditInstanceOnly, meta = (ExposeOnSpawn), BlueprintReadOnly)
	int32 Value;

public:
	virtual FString ToString() const override { return FString::FromInt(Value); }

	virtual EFieldType GetDataType() const override { return EFieldType::Int; }

	virtual bool IsEqual(const UProjectField* Other) const override { return CompareImpl(this, Other); }


	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Project|Field")
	void SetValue(int32 NewValue) { SetValueByRef(Value, NewValue); }

	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Project|Field")
	int32 GetValue() const { return Value; }

protected:
	virtual void ResetImpl() override { Value = 0; }
};

UCLASS()
class HELLAWORLD_API UProjectField_Float : public UProjectField
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditInstanceOnly, meta = (ExposeOnSpawn), BlueprintReadOnly)
	float Value;

public:
	virtual FString ToString() const override { return FString::SanitizeFloat(Value); }

	virtual EFieldType GetDataType() const override { return EFieldType::Float; }

	virtual bool IsEqual(const UProjectField* Other) const override { return CompareImpl(this, Other); }


	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Project|Field")
	void SetValue(float NewValue) { SetValueByRef(Value, NewValue); }

	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Project|Field")
	float GetValue() const { return Value; }

protected:
	virtual void ResetImpl() override { Value = 0; }
};

UCLASS()
class HELLAWORLD_API UProjectField_Vector : public UProjectField
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditInstanceOnly, meta = (ExposeOnSpawn), BlueprintReadOnly)
	FVector Value;

public:
	virtual FString ToString() const override { return Value.ToString(); }

	virtual EFieldType GetDataType() const override { return EFieldType::Vector; }

	virtual bool IsEqual(const UProjectField* Other) const override { return CompareImpl(this, Other); }


	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Project|Field")
	void SetValue(FVector NewValue) { SetValueByRef(Value, NewValue); }

	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Project|Field")
	FVector GetValue() const { return Value; }

protected:
	virtual void ResetImpl() override { Value = FVector::ZeroVector; }
};

UCLASS()
class HELLAWORLD_API UProjectField_Enum : public UProjectField
{
	GENERATED_BODY()

protected:
	/** Use for display */
	UPROPERTY(EditInstanceOnly, meta = (ExposeOnSpawn), BlueprintReadOnly)
	const UEnum* EnumType;

	/** C++ Declared Enum. Has priority over type */
	UPROPERTY(EditInstanceOnly, meta = (ExposeOnSpawn), BlueprintReadOnly)
	FString EnumName;

	UPROPERTY(EditInstanceOnly, meta = (ExposeOnSpawn), BlueprintReadOnly)
	uint8 Value;

public:
#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif


	virtual FString ToString() const override { return EnumType ? EnumType->GetDisplayNameTextByValue((int64)Value).ToString() : TEXT("Invalid");  }

	virtual EFieldType GetDataType() const override { return EFieldType::Enum; }

	virtual bool IsEqual(const UProjectField* Other) const override { return CompareImpl(this, Other); }

	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Project|Field")
	void SetValue(uint8 NewValue) { SetValueByRef(Value, NewValue); }

	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Project|Field")
	uint8 GetValue() const { return Value; }

protected:
	virtual void ResetImpl() override { Value = 0; }
};


UCLASS()
class HELLAWORLD_API UProjectField_Name : public UProjectField
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditInstanceOnly, meta = (ExposeOnSpawn), BlueprintReadOnly)
	FName Value;

public:
	virtual FString ToString() const override { return Value.ToString(); }

	virtual EFieldType GetDataType() const override { return EFieldType::Name; }

	virtual bool IsEqual(const UProjectField* Other) const override { return CompareImpl(this, Other); }


	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Project|Field")
	void SetValue(FName NewValue) { SetValueByRef(Value, NewValue); }

	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Project|Field")
	FName GetValue() const { return Value; }

protected:
	virtual void ResetImpl() override { Value = NAME_None; }
};

UCLASS()
class HELLAWORLD_API UProjectField_String : public UProjectField
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditInstanceOnly, meta = (ExposeOnSpawn), BlueprintReadOnly)
	FString Value;

public:
	virtual FString ToString() const override { return Value; }

	virtual EFieldType GetDataType() const override { return EFieldType::String; }

	virtual bool IsEqual(const UProjectField* Other) const override { return CompareImpl(this, Other); }


	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Project|Field")
	void SetValue(FString NewValue) { SetValueByRef(Value, NewValue); }

	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Project|Field")
	FString GetValue() const { return Value; }

protected:
	virtual void ResetImpl() override { Value.Empty(); }
};


UCLASS()
class HELLAWORLD_API UProjectField_DateTime : public UProjectField
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditInstanceOnly, meta = (ExposeOnSpawn), BlueprintReadOnly)
	FDateTime Value;

	/** Relevant DateTime components in comparisons */
	UPROPERTY(EditInstanceOnly, meta = (ExposeOnSpawn, Bitmask, BitmaskEnum = EDateTimeRelevancy), BlueprintReadOnly)
	int32 Relevancy;

public:
	virtual FString ToString() const override { return Value.ToString(); }

	virtual EFieldType GetDataType() const override { return EFieldType::DateTime; }

	virtual bool IsEqual(const UProjectField* Other) const override 
	{ 
		const UProjectField_DateTime* OtherCasted = Cast<UProjectField_DateTime>(Other);
		return OtherCasted ? Compare(OtherCasted->Value) : false;
	}


	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Project|Field")
	void SetValue(FDateTime NewValue) { SetValueByRef(Value, NewValue); }

	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Project|Field")
	FDateTime GetValue() const { return Value; }


	/** Compare with DateTime using Field's Relevancy mask */
	UFUNCTION(BlueprintCallable, Category = "HellaWorld|Project|Field", BlueprintPure)
	bool Compare(const FDateTime& Other) const;


protected:
	virtual void ResetImpl() override { Value = FDateTime(); }
};



