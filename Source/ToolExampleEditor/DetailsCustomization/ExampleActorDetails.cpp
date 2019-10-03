
#include "ToolExampleEditor/ToolExampleEditor.h"
#include "ExampleActorDetails.h"

#include "DetailsCustomization/ExampleActor.h"

TSharedRef<IDetailCustomization> FExampleActorDetails::MakeInstance()
{
	return MakeShareable(new FExampleActorDetails);
}

void FExampleActorDetails::CustomizeDetails(IDetailLayoutBuilder& DetailLayout)
{	
	TArray<TWeakObjectPtr<UObject>> Objects;
	DetailLayout.GetObjectsBeingCustomized(Objects);
	if (Objects.Num() != 1)
	{
		// skip customization if select more than one objects
		return;
	}
	AExampleActor* actor = (AExampleActor*)Objects[0].Get();

	// hide original property
	DetailLayout.HideProperty(DetailLayout.GetProperty(GET_MEMBER_NAME_CHECKED(AExampleActor, bOption1)));
	DetailLayout.HideProperty(DetailLayout.GetProperty(GET_MEMBER_NAME_CHECKED(AExampleActor, bOption2)));

	// add custom widget to "Options" category
	IDetailCategoryBuilder& OptionsCategory = DetailLayout.EditCategory("Options", FText::FromString(""), ECategoryPriority::Important);
	OptionsCategory.AddCustomRow(FText::FromString("Options"))
				.WholeRowContent()
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.AutoWidth()
					.VAlign(VAlign_Center)
					[
						SNew(SCheckBox)
						.Style(FEditorStyle::Get(), "RadioButton")
						.IsChecked(this, &FExampleActorDetails::IsModeRadioChecked, actor, 1)
						.OnCheckStateChanged(this, &FExampleActorDetails::OnModeRadioChanged, actor, 1)
						[
							SNew(STextBlock).Text(FText::FromString("Option 1"))
						]
					]
					+ SHorizontalBox::Slot()
					.AutoWidth()
					.Padding(10.f, 0.f, 0.f, 0.f)
					.VAlign(VAlign_Center)
					[
						SNew(SCheckBox)
						.Style(FEditorStyle::Get(), "RadioButton")
						.IsChecked(this, &FExampleActorDetails::IsModeRadioChecked, actor, 2)
						.OnCheckStateChanged(this, &FExampleActorDetails::OnModeRadioChanged, actor, 2)
						[
							SNew(STextBlock).Text(FText::FromString("Option 2"))
						]
					]
				];
	
}

ECheckBoxState FExampleActorDetails::IsModeRadioChecked(AExampleActor* actor, int optionIndex) const
{
	bool bFlag = false;
	if (actor)
	{
		if (optionIndex == 1)
			bFlag = actor->bOption1;
		else if (optionIndex == 2)
			bFlag = actor->bOption2;
	}
	return bFlag ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
}

void FExampleActorDetails::OnModeRadioChanged(ECheckBoxState CheckType, AExampleActor* actor, int optionIndex)
{
	bool bFlag = (CheckType == ECheckBoxState::Checked);
	if (actor)
	{
		actor->Modify();
		if (bFlag)
		{
			// clear all options first
			actor->bOption1 = false;
			actor->bOption2 = false;
		}
		if (optionIndex == 1)
			actor->bOption1 = bFlag;
		else if (optionIndex == 2)
			actor->bOption2 = bFlag;
	}
}