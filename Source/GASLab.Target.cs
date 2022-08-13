// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GASLabTarget : TargetRules
{
	public GASLabTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("GASLab");
	}
}