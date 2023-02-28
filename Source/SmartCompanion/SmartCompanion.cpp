// Copyright Epic Games, Inc. All Rights Reserved.

#include "SmartCompanion.h"
#include "Modules/ModuleManager.h"

void SmartCompanionModule::StartupModule()
{
	const FString BasePluginDir = "D:/SmartCompanion/SmartCompanion";

	const FString LibVoskPath = FPaths::Combine(*BasePluginDir, TEXT("Binaries/Win64/libvosk.dll"));
	const FString LibPortAudioPath = FPaths::Combine(*BasePluginDir, TEXT("Binaries/Win64/portaudio_x64.dll"));

	DynamicLibVoskHandle = FPlatformProcess::GetDllHandle(*LibVoskPath);
	DynamicLibPortAudioHandle = FPlatformProcess::GetDllHandle(*LibPortAudioPath);

	if (DynamicLibVoskHandle)
	{
		UE_LOG(LogTemp, Log, TEXT("libvosk.dll loaded successfully!"));
	}
	else
	{
		UE_LOG(LogTemp, Fatal, TEXT("libvosk.dll failed to load!"));
	}

	if (DynamicLibPortAudioHandle)
	{
		UE_LOG(LogTemp, Log, TEXT("portaudio_x64.dll loaded successfully!"));
	}
	else
	{
		UE_LOG(LogTemp, Fatal, TEXT("portaudio_x64.dll failed to load!"));
	}

}

void SmartCompanionModule::ShutdownModule()
{
	FPlatformProcess::FreeDllHandle(DynamicLibVoskHandle);
	DynamicLibVoskHandle = nullptr;

	FPlatformProcess::FreeDllHandle(DynamicLibPortAudioHandle);
	DynamicLibPortAudioHandle = nullptr;
}

IMPLEMENT_PRIMARY_GAME_MODULE(SmartCompanionModule, SmartCompanion, "SmartCompanion" );
 