#pragma once

#include "EditorModes.h"
#include "EdMode.h"

struct HExamplePointProxy : public HHitProxy
{
	DECLARE_HIT_PROXY();

	HExamplePointProxy(UObject* InRefObject, int32 InIndex)
		: HHitProxy(HPP_UI), RefObject(InRefObject), Index(InIndex)
	{}

	UObject* RefObject;
	int32 Index;
};

class AExampleTargetPoint;

class FExampleEdMode : public FEdMode
{
public:

	const static FEditorModeID EM_Example;

	// FEdMode interface
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;
	//virtual void Tick(FEditorViewportClient* ViewportClient, float DeltaTime) override;
	virtual bool HandleClick(FEditorViewportClient* InViewportClient, HHitProxy *HitProxy, const FViewportClick &Click) override;
	virtual bool InputDelta(FEditorViewportClient* InViewportClient, FViewport* InViewport, FVector& InDrag, FRotator& InRot, FVector& InScale) override;
	virtual bool InputKey(FEditorViewportClient* ViewportClient, FViewport* Viewport, FKey Key, EInputEvent Event) override;
	virtual bool ShowModeWidgets() const override;
	virtual bool ShouldDrawWidget() const override;
	virtual bool UsesTransformWidget() const override;
	virtual FVector GetWidgetLocation() const override;
	//virtual bool GetCustomDrawingCoordinateSystem(FMatrix& InMatrix, void* InData) override;
	//virtual bool GetCustomInputCoordinateSystem(FMatrix& InMatrix, void* InData) override;
	//virtual void ActorSelectionChangeNotify() override;
	//virtual void MapChangeNotify() override;
	//virtual void SelectionChanged() override;
	//virtual bool IsCompatibleWith(FEditorModeID OtherModeID) const override;
	// End of FEdMode interface

	FExampleEdMode();
	~FExampleEdMode();

	void AddPoint();
	bool CanAddPoint() const;
	void RemovePoint();
	bool CanRemovePoint() const;
	bool HasValidSelection() const;
	void SelectPoint(AExampleTargetPoint* actor, int32 index);

	TWeakObjectPtr<AExampleTargetPoint> currentSelectedTarget;
	int32 currentSelectedIndex = -1;


	TSharedPtr<FUICommandList> ExampleEdModeActions;
	void MapCommands();
	TSharedPtr<SWidget> GenerateContextMenu(FEditorViewportClient* InViewportClient) const;
	
};