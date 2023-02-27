// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class SmartCompanionModule : public IModuleInterface
{
	public:
		virtual void StartupModule() override;
		virtual void ShutdownModule() override;

		void* DynamicLibVoskHandle;
		void* DynamicLibPortAudioHandle;
};
