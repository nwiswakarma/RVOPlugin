/*
 RVOPlugin 0.0.1
 -----
 
*/
using System.IO;
using System.Collections;
using UnrealBuildTool;

public class RVOPlugin: ModuleRules
{
	public RVOPlugin(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
            new string[] {
                "Core",
                "CoreUObject",
                "Engine"
            });

		PrivateDependencyModuleNames.AddRange(new string[] { });

        // -- RVO include and lib path

        PrivateIncludePaths.AddRange(
            new string[] {
                Path.Combine(ModuleDirectory, "Private/ThirdParty/RVO2-3D"),
            }
        );

        //string ThirdPartyPath = Path.Combine(ModuleDirectory, "../../ThirdParty");

        //string RVOPath = Path.Combine(ThirdPartyPath, "RVO2-3D");
        //string RVOInclude = Path.Combine(RVOPath, "include");
        //string RVOLib = Path.Combine(RVOPath, "lib");

		//PrivateIncludePaths.Add(Path.GetFullPath(RVOInclude));
        //PublicLibraryPaths.Add(Path.GetFullPath(RVOLib));

        //PublicAdditionalLibraries.Add("RVO.lib");
	}
}
