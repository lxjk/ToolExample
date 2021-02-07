#include "ExampleEdMode.h"
#include "ToolExampleEditor/ToolExampleEditor.h"
#include "Editor/UnrealEd/Public/Toolkits/ToolkitManager.h"
#include "ScopedTransaction.h"
#include "ExampleEdModeToolkit.h"
#include "EditorMode/ExampleTargetPoint.h"

class ExampleEditorCommands : public TCommands<ExampleEditorCommands>
{
public:
	ExampleEditorCommands() : TCommands <ExampleEditorCommands>
		(
			"ExampleEditor",	// Context name for fast lookup
			FText::FromString(TEXT("Example Editor")),	// context name for displaying
			NAME_None,	// Parent
			FEditorStyle::GetStyleSetName()
			)
	{
	}

#define LOCTEXT_NAMESPACE ""
	virtual void RegisterCommands() override
	{
		UI_COMMAND(DeletePoint, "Delete Point", "Delete the currently selected point.", EUserInterfaceActionType::Button, FInputGesture(EKeys::Delete));
	}
#undef LOCTEXT_NAMESPACE

public:
	TSharedPtr<FUICommandInfo> DeletePoint;
};

IMPLEMENT_HIT_PROXY(HExamplePointProxy, HHitProxy);

const FEditorModeID FExampleEdMode::EM_Example(TEXT("EM_Example"));

FExampleEdMode::FExampleEdMode()
{
	ExampleEditorCommands::Register();
	ExampleEdModeActions = MakeShareable(new FUICommandList);
}

FExampleEdMode::~FExampleEdMode()
{
	ExampleEditorCommands::Unregister();
}

void FExampleEdMode::MapCommands()
{
	const auto& Commands = ExampleEditorCommands::Get();

	ExampleEdModeActions->MapAction(
		Commands.DeletePoint,
		FExecuteAction::CreateSP(this, &FExampleEdMode::RemovePoint),
		FCanExecuteAction::CreateSP(this, &FExampleEdMode::CanRemovePoint));
}

void FExampleEdMode::Enter()
{
	FEdMode::Enter();
	
	if (!Toolkit.IsValid())
	{
		Toolkit = MakeShareable(new FExampleEdModeToolkit);
		Toolkit->Init(Owner->GetToolkitHost());
	}

	// reset
	currentSelectedTarget = nullptr;
	currentSelectedIndex = -1;

	MapCommands();
}

void FExampleEdMode::Exit()
{
	FToolkitManager::Get().CloseToolkit(Toolkit.ToSharedRef());
	Toolkit.Reset();
	
	FEdMode::Exit();
}

void FExampleEdMode::Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI)
{
	const FColor normalColor(200, 200, 200);
	const FColor selectedColor(255, 128, 0);

	UWorld* World = GetWorld();
	for (TActorIterator<AExampleTargetPoint> It(World); It; ++It)
	{
		AExampleTargetPoint* actor = (*It);
		if (actor)
		{
			FVector actorLoc = actor->GetActorLocation();
			for (int i = 0; i < actor->Points.Num(); ++i)
			{
				bool bSelected = (actor == currentSelectedTarget && i == currentSelectedIndex);
				const FColor& color = bSelected ? selectedColor : normalColor;
				// set hit proxy and draw
				PDI->SetHitProxy(new HExamplePointProxy(actor, i));
				PDI->DrawPoint(actor->Points[i], color, 15.f, SDPG_Foreground);
				PDI->DrawLine(actor->Points[i], actorLoc, color, SDPG_Foreground);
				PDI->SetHitProxy(NULL);
			}
		}
	}

	FEdMode::Render(View, Viewport, PDI);
}

bool FExampleEdMode::HandleClick(FEditorViewportClient* InViewportClient, HHitProxy *HitProxy, const FViewportClick &Click)
{
	bool isHandled = false;

	if (HitProxy)
	{
		if (HitProxy->IsA(HExamplePointProxy::StaticGetType()))
		{
			isHandled = true;
			HExamplePointProxy* examplePointProxy = (HExamplePointProxy*)HitProxy;
			AExampleTargetPoint* actor = Cast<AExampleTargetPoint>(examplePointProxy->RefObject);
			int32 index = examplePointProxy->Index;
			if (actor && index >= 0 && index < actor->Points.Num())
			{
				SelectPoint(actor, index);
			}
		}
	}

	if (HitProxy && isHandled && Click.GetKey() == EKeys::RightMouseButton)
	{
		TSharedPtr<SWidget> MenuWidget = GenerateContextMenu(InViewportClient);
		if (MenuWidget.IsValid())
		{
			FSlateApplication::Get().PushMenu(
				Owner->GetToolkitHost()->GetParentWidget(),
				FWidgetPath(),
				MenuWidget.ToSharedRef(),
				FSlateApplication::Get().GetCursorPos(),
				FPopupTransitionEffect(FPopupTransitionEffect::ContextMenu));
		}
	}

	return isHandled;
}

bool FExampleEdMode::InputDelta(FEditorViewportClient* InViewportClient, FViewport* InViewport, FVector& InDrag, FRotator& InRot, FVector& InScale)
{
	if (InViewportClient->GetCurrentWidgetAxis() == EAxisList::None)
	{
		return false;
	}
	
	if (HasValidSelection())
	{
		if (!InDrag.IsZero())
		{
			currentSelectedTarget->Modify();
			currentSelectedTarget->Points[currentSelectedIndex] += InDrag;
		}
		return true;
	}

	return false;
}

bool FExampleEdMode::InputKey(FEditorViewportClient* ViewportClient, FViewport* Viewport, FKey Key, EInputEvent Event)
{
	bool isHandled = false;

	if (!isHandled && Event == IE_Pressed)
	{
		isHandled = ExampleEdModeActions->ProcessCommandBindings(Key, FSlateApplication::Get().GetModifierKeys(), false);
	}

	return isHandled;
}

TSharedPtr<SWidget> FExampleEdMode::GenerateContextMenu(FEditorViewportClient* InViewportClient) const
{
	FMenuBuilder MenuBuilder(true, NULL);

	MenuBuilder.PushCommandList(ExampleEdModeActions.ToSharedRef());
	MenuBuilder.BeginSection("Example Section");
	if (HasValidSelection())
	{
		// add label for point index
		TSharedRef<SWidget> LabelWidget =
			SNew(STextBlock)
			.Text(FText::FromString(FString::FromInt(currentSelectedIndex)))
			.ColorAndOpacity(FLinearColor::Green);
		MenuBuilder.AddWidget(LabelWidget, FText::FromString(TEXT("Point Index: ")));
		MenuBuilder.AddMenuSeparator();
		// add delete point entry
		MenuBuilder.AddMenuEntry(ExampleEditorCommands::Get().DeletePoint);
	}
	MenuBuilder.EndSection();
	MenuBuilder.PopCommandList();

	TSharedPtr<SWidget> MenuWidget = MenuBuilder.MakeWidget();
	return MenuWidget;
}

bool FExampleEdMode::ShowModeWidgets() const
{
	return true;
}

bool FExampleEdMode::ShouldDrawWidget() const
{
	return true;
}

bool FExampleEdMode::UsesTransformWidget() const
{
	return true;
}

FVector FExampleEdMode::GetWidgetLocation() const
{
	if (HasValidSelection())
	{
		return currentSelectedTarget->Points[currentSelectedIndex];
	}
	return FEdMode::GetWidgetLocation();
}

AExampleTargetPoint* GetSelectedTargetPointActor()
{
	TArray<UObject*> selectedObjects;
	GEditor->GetSelectedActors()->GetSelectedObjects(selectedObjects);
	if (selectedObjects.Num() == 1)
	{
		return Cast<AExampleTargetPoint>(selectedObjects[0]);
	}
	return nullptr;
}

void FExampleEdMode::AddPoint()
{
	AExampleTargetPoint* actor = GetSelectedTargetPointActor();
	if (actor)
	{
		const FScopedTransaction Transaction(FText::FromString("Add Point"));

		// add new point, slightly in front of camera
		FEditorViewportClient* client = (FEditorViewportClient*)GEditor->GetActiveViewport()->GetClient();
		FVector newPoint = client->GetViewLocation() + client->GetViewRotation().Vector() * 50.f;
		actor->Modify();
		actor->Points.Add(newPoint);
		// auto select this new point
		SelectPoint(actor, actor->Points.Num() - 1);
	}
}

bool FExampleEdMode::CanAddPoint() const
{
	return GetSelectedTargetPointActor() != nullptr;
}

void FExampleEdMode::RemovePoint()
{
	if (HasValidSelection())
	{
		const FScopedTransaction Transaction(FText::FromString("Remove Point"));

		currentSelectedTarget->Modify();
		currentSelectedTarget->Points.RemoveAt(currentSelectedIndex);
		// deselect the point
		SelectPoint(nullptr, -1);
	}
}

bool FExampleEdMode::CanRemovePoint() const
{
	return HasValidSelection();
}

bool FExampleEdMode::HasValidSelection() const
{
	return currentSelectedTarget.IsValid() && currentSelectedIndex >= 0 && currentSelectedIndex < currentSelectedTarget->Points.Num();
}

void FExampleEdMode::SelectPoint(AExampleTargetPoint* actor, int32 index)
{
	currentSelectedTarget = actor;
	currentSelectedIndex = index;

	// select this actor only
	if (currentSelectedTarget.IsValid())
	{
		GEditor->SelectNone(true, true);
		GEditor->SelectActor(currentSelectedTarget.Get(), true, true);
	}
}