#pragma once

#include "IDetailCustomization.h"

class AExampleActor;

class FExampleActorDetails : public IDetailCustomization
{
public:
	/** Makes a new instance of this detail layout class for a specific detail view requesting it */
	static TSharedRef<IDetailCustomization> MakeInstance();

	/** IDetailCustomization interface */
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;

protected:

	// widget functions
	ECheckBoxState IsModeRadioChecked(AExampleActor* actor, int optionIndex) const;
	void OnModeRadioChanged(ECheckBoxState CheckType, AExampleActor* actor, int optionIndex);

};