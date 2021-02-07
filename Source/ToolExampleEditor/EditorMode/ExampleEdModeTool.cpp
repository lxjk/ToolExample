#include "ToolExampleEditor/ToolExampleEditor.h"
#include "ExampleEdModeTool.h"
#include "ExampleEdMode.h"

#define IMAGE_BRUSH(RelativePath, ...) FSlateImageBrush(StyleSet->RootToContentDir(RelativePath, TEXT(".png")), __VA_ARGS__)

TSharedPtr< FSlateStyleSet > ExampleEdModeTool::StyleSet = nullptr;

void ExampleEdModeTool::OnStartupModule()
{
	RegisterStyleSet();
	RegisterEditorMode();
}

void ExampleEdModeTool::OnShutdownModule()
{
	UnregisterStyleSet();
	UnregisterEditorMode();
}

void ExampleEdModeTool::RegisterStyleSet()
{
	// Const icon sizes
	const FVector2D Icon20x20(20.0f, 20.0f);
	const FVector2D Icon40x40(40.0f, 40.0f);

	// Only register once
	if (StyleSet.IsValid())
	{
		return;
	}

	StyleSet = MakeShareable(new FSlateStyleSet("ExampleEdModeToolStyle"));
	StyleSet->SetContentRoot(FPaths::ProjectDir() / TEXT("Content/EditorResources"));
	StyleSet->SetCoreContentRoot(FPaths::ProjectDir() / TEXT("Content/EditorResources"));

	// Spline editor
	{
		StyleSet->Set("ExampleEdMode", new IMAGE_BRUSH(TEXT("IconExampleEditorMode"), Icon40x40));
		StyleSet->Set("ExampleEdMode.Small", new IMAGE_BRUSH(TEXT("IconExampleEditorMode"), Icon20x20));
	}

	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());
}

void ExampleEdModeTool::UnregisterStyleSet()
{
	if (StyleSet.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet.Get());
		ensure(StyleSet.IsUnique());
		StyleSet.Reset();
	}
}

void ExampleEdModeTool::RegisterEditorMode()
{
	FEditorModeRegistry::Get().RegisterMode<FExampleEdMode>(
		FExampleEdMode::EM_Example,
		FText::FromString("Example Editor Mode"),
		FSlateIcon(StyleSet->GetStyleSetName(), "ExampleEdMode", "ExampleEdMode.Small"),
		true, 500
		);
}

void ExampleEdModeTool::UnregisterEditorMode()
{
	FEditorModeRegistry::Get().UnregisterMode(FExampleEdMode::EM_Example);
}

#undef IMAGE_BRUSH