// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UnrealEd.h"
//#include "Engine.h"
#include "SlateBasics.h"
#include "SlateExtras.h"
//#include "Internationalization.h"
//#include "MultiBoxExtender.h"
#include "Editor/LevelEditor/Public/LevelEditor.h"
#include "Editor/PropertyEditor/Public/PropertyEditing.h"
#include "IAssetTypeActions.h"

#include "IExampleModuleInterface.h"

class FToolExampleEditor : public IExampleModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	virtual void AddModuleListeners() override;

	/**
	* Singleton-like access to this module's interface.  This is just for convenience!
	* Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already.
	*
	* @return Returns singleton instance, loading the module on demand if needed
	*/
	static inline FToolExampleEditor& Get()
	{
		return FModuleManager::LoadModuleChecked< FToolExampleEditor >("ToolExampleEditor");
	}

	/**
	* Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true.
	*
	* @return True if the module is loaded and ready to use
	*/
	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("ToolExampleEditor");
	}

	void AddMenuExtension(const FMenuExtensionDelegate &extensionDelegate, FName extensionHook, const TSharedPtr<FUICommandList> &CommandList = NULL, EExtensionHook::Position position = EExtensionHook::Before);
	TSharedRef<FWorkspaceItem> GetMenuRoot() { return MenuRoot; };

protected:
	TSharedPtr<FExtensibilityManager> LevelEditorMenuExtensibilityManager;
	TSharedPtr<FExtender> MenuExtender;

	static TSharedRef<FWorkspaceItem> MenuRoot;

	TArray<TSharedPtr<IAssetTypeActions>> CreatedAssetTypeActions;

	void MakePulldownMenu(FMenuBarBuilder &menuBuilder);
	void FillPulldownMenu(FMenuBuilder &menuBuilder);
};