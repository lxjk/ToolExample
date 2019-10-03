#pragma once

#include "SDockTab.h"
#include "SDockableTab.h"
#include "SDockTabStack.h"
#include "SlateApplication.h"
#include "TabTool.h"

class TabToolPanel : public SCompoundWidget
{

	SLATE_BEGIN_ARGS(TabToolPanel)
	{}

	SLATE_ARGUMENT(TWeakPtr<class TabTool>, Tool)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

protected:

	TWeakPtr<TabTool> tool;
};