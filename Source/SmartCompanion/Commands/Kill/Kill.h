#pragma once

#include "../ICommand.h"
#include "../../SmartModules/ComputerVisionModule/ComputerVisionModule.h"

class Kill : public ICommand
{
	protected:
		ComputerVisionModule computerVisionModule;
	
	public:
		Kill();
		Kill(ComputerVisionModule& _computerVisionModule);

		void Run() override;
};