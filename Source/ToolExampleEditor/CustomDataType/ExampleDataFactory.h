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
	// End UFactory Interface
};