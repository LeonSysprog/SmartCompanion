#include "CommandHandler.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "../../SmartCompanionCharacter.h"
#include "../Kill/KillRed/KillRed.h"
#include "../Kill/KillBlue/KillBlue.h"

#pragma region Main Thread Code

CommandHandler::CommandHandler()
{
	isActivateSpeechRecognition = false;
	thread = FRunnableThread::Create(this, TEXT("CommandHandlerThread"));
}

CommandHandler::CommandHandler(UWorld* _worldContext) :
	worldContext(_worldContext),
	speechRecoginitonModule(_worldContext),
	computerVisionModule(_worldContext)
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

	commandStorage.Add(TEXT("kill red"), TSharedPtr<ICommand>(new KillRed()));
	commandStorage.Add(TEXT("kill blue"), TSharedPtr<ICommand>(new KillBlue()));

	speechRecoginitonModule.Initialize();
	computerVisionModule.Initialize();

	return true;
}

uint32 CommandHandler::Run()
{
	while (bRunThread)
	{
		if (isActivateSpeechRecognition)
		{
			auto text = speechRecoginitonModule.Run();

			auto pos = text.find("green");
			if (pos != std::string::npos)
			{
				float angle = computerVisionModule.Run();

				auto controller = UGameplayStatics::GetPlayerController(worldContext, 0);
				auto character = (ASmartCompanionCharacter*)(controller->GetPawn());

				auto rotation = FQuat(FRotator(0.0, angle, 0.0));
				character->AddActorLocalRotation(rotation, false, 0, ETeleportType::None);
			}
		}
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
