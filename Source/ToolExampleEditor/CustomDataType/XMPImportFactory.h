// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "Factories/ImportSettings.h"
#include "XMPImportFactory.generated.h"

UCLASS(customconstructor)
class UXMPImportFactory : public UFactory
{
	GENERATED_UCLASS_BODY()

public:
	UXMPImportFactory(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual FText GetDisplayName() const override;
	virtual UObject* FactoryCreateText(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const TCHAR*& Buffer, const TCHAR* BufferEnd, FFeedbackContext* Warn, bool& bOutOperationCanceled) override;
	virtual bool FactoryCanImport(const FString& Filename) override;
};
