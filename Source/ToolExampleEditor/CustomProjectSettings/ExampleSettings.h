#pragma once

#include "ExampleSettings.generated.h"

UCLASS(config = EditorUserSettings, defaultconfig)
class UExampleSettings : public UObject
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, config, Category = Test)
	bool bTest = false;
};