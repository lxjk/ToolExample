// Fill out your copyright notice in the Description page of Project Settings.


#include "XMPImportFactory.h"
#include "ToolExample/CustomDataType/ExampleData.h"
#include "EditorFramework/AssetImportData.h"

#define LOCTEXT_NAMESPACE "XMPImportFactory"

UXMPImportFactory::UXMPImportFactory(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	SupportedClass = UExampleData::StaticClass();
	bCreateNew = false;
	bEditorImport = true;
	bEditAfterNew = true;
	bText = true;

	Formats.Add(TEXT("xmp;Example Data"));
}

FText UXMPImportFactory::GetDisplayName() const
{
	return LOCTEXT("XMPImportFactoryDisplayName", "Example Data");
}

UObject* UXMPImportFactory::FactoryCreateText(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const TCHAR*& Buffer, const TCHAR* BufferEnd, FFeedbackContext* Warn, bool& bOutOperationCanceled)
{
	GEditor->GetEditorSubsystem<UImportSubsystem>()->BroadcastAssetPreImport(this, InClass, InParent, InName, Type);

	UExampleData* ExampleData = CastChecked<UExampleData>(NewObject<UExampleData>(InParent, InName, Flags));
	const int32 NumChars = BufferEnd - Buffer;
	ExampleData->ExampleString = FString(NumChars, Buffer);
	ExampleData->SourceFilePath = UAssetImportData::SanitizeImportFilename(CurrentFilename, ExampleData->GetOutermost());

	GEditor->GetEditorSubsystem<UImportSubsystem>()->BroadcastAssetPostImport(this, ExampleData);

	return ExampleData;
}

bool UXMPImportFactory::FactoryCanImport(const FString& Filename)
{
	return FPaths::GetExtension(Filename).Equals(TEXT("xmp"));
}
