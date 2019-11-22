// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class HellaWorldEditor : ModuleRules
{
	public HellaWorldEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "HellaWorld", "Core", "CoreUObject", "Engine", "InputCore", "EditorStyle" });

		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore", "EditorStyle" });

        //         PublicIncludePaths.AddRange(
        //         new string[]
        //         {
        //             "HellaWorldEditor/Public"
        //         });
        // 
        //         PrivateIncludePaths.AddRange(
        //         new string[]
        //         {
        //             "HellaWorldEditor/Private"
        //         });
        //         

        PrivateDependencyModuleNames.AddRange(
       new string[]
       {
           // k2node   
           "KismetCompiler",
           "BlueprintGraph"
       }
   );

    }
}
