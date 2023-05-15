#pragma once

#include "CoreMinimal.h"
#include "HAL/Runnable.h"
#include "../ICommand.h"
#include "../../SmartModules/SpeechRecognitionModule/SpeechRecognitionModule.h"

class CommandHandler : public FRunnable
{
	public:
		CommandHandler();
		~CommandHandler();

		bool Init() override;
		uint32 Run() override;
		void Stop() override;

		void Activate();
		void Deactivate();

	private:
		FRunnableThread* thread;
		bool bRunThread;

		bool isActivateSpeechRecognition;

		TMap<FString, TSharedPtr<ICommand>> commandStorage;
		SpeechRecognitionModule speechRecoginitonModule;
};