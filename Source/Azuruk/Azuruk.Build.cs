

using UnrealBuildTool;

public class Azuruk : ModuleRules
{
	public Azuruk(TargetInfo Target)
	{
        PrivateIncludePaths.AddRange(
            new string[] { 
                "Azuruk",
				"Azuruk/Character",
                "Azuruk/Controllers",
                "Azuruk/UI",
                "Azuruk/Abilities",
                "Azuruk/Effects",
            }
        );

		PublicDependencyModuleNames.AddRange(
            new string[] { 
                "Core", 
                "CoreUObject", 
                "Engine", 
                "InputCore" 
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[] {
				"Slate",
                "SlateCore",
			}
        );
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");
		// if ((Target.Platform == UnrealTargetPlatform.Win32) || (Target.Platform == UnrealTargetPlatform.Win64))
		// {
		//		if (UEBuildConfiguration.bCompileSteamOSS == true)
		//		{
		//			DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");
		//		}
		// }
	}
}
