// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class SnakeGame : ModuleRules
{
	public SnakeGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "EnhancedInput", "Niagara" });
		
		PublicIncludePaths.AddRange(new string[] { "SnakeGame" });

		if (base.Target.Configuration != UnrealTargetConfiguration.Shipping)
		{
			PublicDependencyModuleNames.Add("FunctionalTesting");
		}
	}
}
