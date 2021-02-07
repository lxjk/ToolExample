#pragma once

#include "Toolkits/BaseToolkit.h"
#include "ExampleEdMode.h"
#include "SExampleEdModeWidget.h"

class FExampleEdModeToolkit: public FModeToolkit
{
public:

	FExampleEdModeToolkit()
	{
		SAssignNew(ExampleEdModeWidget, SExampleEdModeWidget);
	}

	/** IToolkit interface */
	virtual FName GetToolkitFName() const override { return FName("ExampleEdMode"); }
	virtual FText GetBaseToolkitName() const override { return NSLOCTEXT("BuilderModeToolkit", "DisplayName", "Builder"); }
	virtual class FEdMode* GetEditorMode() const override { return GLevelEditorModeTools().GetActiveMode(FExampleEdMode::EM_Example); }
	virtual TSharedPtr<class SWidget> GetInlineContent() const override { return ExampleEdModeWidget; }

private:

	TSharedPtr<SExampleEdModeWidget> ExampleEdModeWidget;
};
