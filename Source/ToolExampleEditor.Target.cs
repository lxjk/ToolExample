// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class ToolExampleEditorTarget : TargetRules
{
	public ToolExampleEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "ToolExample" } );
        ExtraModuleNames.AddRange( new string[] { "ToolExampleEditor" });
    }
}
