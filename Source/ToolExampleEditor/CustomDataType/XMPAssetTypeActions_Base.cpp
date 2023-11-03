// Fill out your copyright notice in the Description page of Project Settings.


#include "XMPAssetTypeActions_Base.h"
#include "ToolExample/CustomDataType/ExampleData.h"
#include "EditorReimportHandler.h"
#include "EditorFramework/AssetImportData.h"
#include "Misc/FileHelper.h"

bool FXMPAssetTypeActions_Base::CanReimport(UObject* Obj, TArray<FString>& OutFilenames)
{
	UExampleData* ExampleData = Cast<UExampleData>(Obj);
	if (ExampleData)
	{
		OutFilenames.Add(UAssetImportData::ResolveImportFilename(ExampleData->SourceFilePath, ExampleData->GetOutermost()));
		return true;
	}
	return false;
}

void FXMPAssetTypeActions_Base::SetReimportPaths(UObject* Obj, const TArray<FString>& NewReimportPaths)
{
	check(NewReimportPaths.IsValidIndex(0));
	if (UExampleData* ExampleData = Cast<UExampleData>(Obj))
	{
		ExampleData->SourceFilePath = UAssetImportData::SanitizeImportFilename(NewReimportPaths[0], ExampleData->GetOutermost());
	}
}

EReimportResult::Type FXMPAssetTypeActions_Base::Reimport(UObject* Obj)
{
	UExampleData* ExampleData = Cast<UExampleData>(Obj);
	if (!ExampleData)
	{
		return EReimportResult::Failed;
	}

	const FString Filename = UAssetImportData::ResolveImportFilename(ExampleData->SourceFilePath, ExampleData->GetOutermost());

	FString Data;
	if (FFileHelper::LoadFileToString(Data, *Filename))
	{
		const TCHAR* Ptr = *Data;
		ExampleData->Modify();
		ExampleData->MarkPackageDirty();

		ExampleData->ExampleString = Ptr;
		ExampleData->SourceFilePath = UAssetImportData::SanitizeImportFilename(Filename, ExampleData->GetOutermost());
	}

	return EReimportResult::Succeeded;
}

void FXMPAssetTypeActions_Base::ExecuteReimport(TArray<TWeakObjectPtr<UExampleData>> Objects)
{
	for (auto ObjIt = Objects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		auto Object = (*ObjIt).Get();
		if (Object)
		{
			Reimport(Object);
		}
	}
}
