#pragma once
#include "UnrealEd.h"
#include "ExampleDataFactory.generated.h"

UCLASS()
class UExampleDataFactory : public UFactory
{
	GENERATED_UCLASS_BODY()
public:
	// Begin UFactory Interface
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	virtual UObject* FactoryCreateText(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const TCHAR*& Buffer, const TCHAR* BufferEnd, FFeedbackContext* Warn) override;
	virtual bool FactoryCanImport(const FString& Filename) override;
	// End UFactory Interface

	// helper function
	static void MakeExampleDataFromText(class UExampleData* Data, const TCHAR*& Buffer, const TCHAR* BufferEnd);
};