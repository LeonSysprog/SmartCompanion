#include "CommandHandler.h"
#include "../Hide/Hide.h"
#include "../Kill/KillRed/KillRed.h"
#include "../Kill/KillBlue/KillBlue.h"
#include <GenericPlatform/GenericPlatformProcess.h>

#pragma region Main Thread Code

CommandHandler::CommandHandler()
{
	isActivateSpeechRecognition = false;
	thread = FRunnableThread::Create(this, TEXT("CommandHandlerThread"));
}

CommandHandler::~CommandHandler()
{
	speechRecoginitonModule.Shutdown();

	if (thread)
	{
		thread->Kill();
		delete thread;
	}
}

#pragma endregion

bool CommandHandler::Init()
{
	UE_LOG(LogTemp, Display, TEXT("CommandHandler initialize"));

	commandStorage.Add(TEXT("hide"), TSharedPtr<ICommand>(new Hide()));
	commandStorage.Add(TEXT("kill red"), TSharedPtr<ICommand>(new KillRed()));
	commandStorage.Add(TEXT("kill blue"), TSharedPtr<ICommand>(new KillBlue()));

	speechRecoginitonModule.Initialize();

	return true;
}

uint32 CommandHandler::Run()
{
	while (bRunThread)
	{
		if (isActivateSpeechRecognition) speechRecoginitonModule.Run();
	}

	return 0;
}

void CommandHandler::Stop()
{
	bRunThread = false;
}

void CommandHandler::Activate()
{
	isActivateSpeechRecognition = true;
}

void CommandHandler::Deactivate()
{
	isActivateSpeechRecognition = false;
}
