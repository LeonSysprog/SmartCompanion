#pragma once

#include "../ISmartModule.h"

#pragma comment(lib, "D:\\SmartCompanion\\SmartCompanion\\ThirdParty\\PortAudio\\Lib\\Release\\portaudio_static_x64.lib")
#pragma comment(lib, "D:\\SmartCompanion\\SmartCompanion\\ThirdParty\\Vosk\\vosk-win64\\libvosk.lib")

#include "..\..\..\..\ThirdParty\PortAudio\Include\portaudio.h"
#include "..\..\..\..\ThirdParty\Vosk\vosk-win64\vosk_api.h"

class SpeechRecognitionModule : public ISmartModule
{
	private:
		/** speech recognition vars **/
		VoskModel* model;
		VoskRecognizer* recognizer;
		PaStream* stream;
		// сборщик мусора должен захватить
		char data[4096];

	public:
		void Initialize() override;
		void Run() override;
		void Shutdown() override;
};