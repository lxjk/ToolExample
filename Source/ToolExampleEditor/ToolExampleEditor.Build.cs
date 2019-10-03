// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.IO;

public class ToolExampleEditor : ModuleRules
{
	public ToolExampleEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PublicIncludePaths.AddRange(
            new string[] {
					// ... add public include paths required here ...
            }
            );

        PrivateIncludePaths.AddRange(
            new string[] {
                // ... add other private include paths required here ...
            }
            );

        PublicDependencyModuleNames.AddRange(
            new string[] {
                "Core",
                "Engine",
                "CoreUObject",
                "InputCore",
                "LevelEditor",
                "Slate",
                "EditorStyle",
                "AssetTools",
                "EditorWidgets",
                "UnrealEd",
                "BlueprintGraph",
                "AnimGraph",
                "ComponentVisualizers",
                "ToolExample"
        }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "AppFramework",
                "SlateCore",
                "AnimGraph",
                "UnrealEd",
                "KismetWidgets",
                "MainFrame",
                "PropertyEditor",
                "ComponentVisualizers",
                "ToolExample"
                // ... add private dependencies that you statically link with here ...
            }
            );
    }
}
