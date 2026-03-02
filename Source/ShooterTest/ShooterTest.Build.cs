// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ShooterTest : ModuleRules
{
	public ShooterTest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"ShooterTest",
			"ShooterTest/Variant_Platforming",
			"ShooterTest/Variant_Platforming/Animation",
			"ShooterTest/Variant_Combat",
			"ShooterTest/Variant_Combat/AI",
			"ShooterTest/Variant_Combat/Animation",
			"ShooterTest/Variant_Combat/Gameplay",
			"ShooterTest/Variant_Combat/Interfaces",
			"ShooterTest/Variant_Combat/UI",
			"ShooterTest/Variant_SideScrolling",
			"ShooterTest/Variant_SideScrolling/AI",
			"ShooterTest/Variant_SideScrolling/Gameplay",
			"ShooterTest/Variant_SideScrolling/Interfaces",
			"ShooterTest/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
