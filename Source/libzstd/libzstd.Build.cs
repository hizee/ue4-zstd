// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class libzstd : ModuleRules
{
	public libzstd(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicSystemIncludePaths.AddRange(
			new string[] {
				Path.Combine(ModuleDirectory,"ThirdParty/zstd"),
                Path.Combine(ModuleDirectory,"ThirdParty/zstd/common"),
                Path.Combine(ModuleDirectory,"ThirdParty/zstd/compress"),
                Path.Combine(ModuleDirectory,"ThirdParty/zstd/decompress"),
                Path.Combine(ModuleDirectory,"ThirdParty/zstd/deprecated"),
                Path.Combine(ModuleDirectory,"ThirdParty/zstd/dictBuilder"),
                Path.Combine(ModuleDirectory,"ThirdParty/zstd/legacy")
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);

        PublicDefinitions.AddRange(new string[]
        {
            "ZSTD_MULTITHREAD=1",
            "ZSTD_LEGACY_SUPPORT=5"
        });
        bEnableUndefinedIdentifierWarnings = false;

    }
}
