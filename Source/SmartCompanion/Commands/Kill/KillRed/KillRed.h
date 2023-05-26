#pragma once

#include "../Kill.h"

class KillRed : public Kill
{
	public:
		KillRed();
		KillRed(ComputerVisionModule& _computerVisionModule);

		void Run() override;
};