// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class U04_MultiPlay : ModuleRules
{
	public U04_MultiPlay(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] 
		{ 
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"HeadMountedDisplay",
			"UMG",
			"OnlineSubsystem"
		});
	}
}
