// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"
#include "EditorReimportHandler.h"

class UExampleData;

class FXMPAssetTypeActions_Base : public FAssetTypeActions_Base, public FReimportHandler
{
public:
	//It won't be shown in the content browser, it is a proxy for an `Example Data` asset
	virtual FColor GetTypeColor() const override { return FColor(0, 0, 0); }
	virtual bool HasActions(const TArray<UObject*>& InObjects) const override { return true; }
	virtual uint32 GetCategories() override { return EAssetTypeCategories::Misc; }
	virtual bool IsImportedAsset() const override { return true; }

	virtual bool CanReimport(UObject* Obj, TArray<FString>& OutFilenames) override;
	virtual void SetReimportPaths(UObject* Obj, const TArray<FString>& NewReimportPaths) override;
	virtual EReimportResult::Type Reimport(UObject* Obj) override;

protected:
	void ExecuteReimport(TArray<TWeakObjectPtr<UExampleData>> Objects);

};
