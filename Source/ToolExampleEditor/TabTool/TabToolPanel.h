#pragma once

#include "Widgets/Docking/SDockTab.h"
#include "Framework/Application/SlateApplication.h"
#include "TabTool.h"

class TabToolPanel : public SCompoundWidget
{

	SLATE_BEGIN_ARGS(TabToolPanel)
	{
	}

	SLATE_ARGUMENT(TWeakPtr<class TabTool>, Tool)
	SLATE_END_ARGS()

	void Construct(const FArguments &InArgs);

protected:
	TWeakPtr<TabTool> tool;
};