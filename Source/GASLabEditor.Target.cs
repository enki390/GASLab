// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GASLabEditorTarget : TargetRules
{
	public GASLabEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("GASLab");
	}
}