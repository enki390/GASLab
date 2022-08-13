// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GASLab : ModuleRules
{
	public GASLab(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new[]
			{ "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
		PrivateDependencyModuleNames.AddRange(new[]
		{
			"GameplayTags",
			"GameplayAbilities",
			"GameplayTasks"
		});
	}
}