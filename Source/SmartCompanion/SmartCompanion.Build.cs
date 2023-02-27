// Copyright Epic Games, Inc. All Rights Reserved.
using System.IO;
using UnrealBuildTool;

public class SmartCompanion : ModuleRules
{
    public SmartCompanion(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });

		LoadVosk(Target);
		LoadPortAudio(Target);
    }

    public void LoadVosk(ReadOnlyTargetRules Target)
    {
        PublicAdditionalLibraries.Add("D:\\SmartCompanion\\SmartCompanion\\ThirdParty\\Vosk\\vosk-win64\\libvosk.lib");
        PublicIncludePaths.Add("D:\\SmartCompanion\\SmartCompanion\\ThirdParty\\Vosk\\vosk-win64\\vosk_api.h");
        RuntimeDependencies.Add("D:\\SmartCompanion\\SmartCompanion\\ThirdParty\\Vosk\\vosk-win64\\libvosk.dll");
        PublicDelayLoadDLLs.Add("libvosk.dll");
    }

    public void LoadPortAudio(ReadOnlyTargetRules Target)
	{
        PublicAdditionalLibraries.Add("D:\\SmartCompanion\\SmartCompanion\\ThirdParty\\PortAudio\\Lib\\Release\\portaudio_static_x64.lib");
        PublicIncludePaths.Add("D:\\SmartCompanion\\SmartCompanion\\ThirdParty\\PortAudio\\Include\\portaudio.h");
        RuntimeDependencies.Add("D:\\SmartCompanion\\SmartCompanion\\ThirdParty\\PortAudio\\Lib\\Release\\portaudio_x64.dll");
        PublicDelayLoadDLLs.Add("portaudio_x64.dll");
    }
}
