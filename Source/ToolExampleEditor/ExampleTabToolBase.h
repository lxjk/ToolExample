#pragma once

#include "ToolExampleEditor/ToolExampleEditor.h"
#include "ToolExampleEditor/IExampleModuleInterface.h"
#include "TabManager.h"
#include "SDockTab.h"

class FExampleTabToolBase : public IExampleModuleListenerInterface, public TSharedFromThis< FExampleTabToolBase >
{

public:

	// IPixelopusToolBase
	virtual void OnStartupModule() override
	{
		Initialize();
		FGlobalTabmanager::Get()->RegisterNomadTabSpawner(TabName, FOnSpawnTab::CreateRaw(this, &FExampleTabToolBase::SpawnTab))
			.SetGroup(FToolExampleEditor::Get().GetMenuRoot())
			.SetDisplayName(TabDisplayName)
			.SetTooltipText(ToolTipText);
	};

	virtual void OnShutdownModule() override
	{
		FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(TabName);
	};
	
	// In this function set TabName/TabDisplayName/ToolTipText
	virtual void Initialize() {};
	virtual TSharedRef<SDockTab> SpawnTab(const FSpawnTabArgs& TabSpawnArgs) { return SNew(SDockTab); };

	virtual void MakeMenuEntry(FMenuBuilder &menuBuilder)
	{
		FGlobalTabmanager::Get()->PopulateTabSpawnerMenu(menuBuilder, TabName);
	};

protected:
	FName TabName;
	FText TabDisplayName;
	FText ToolTipText;
};