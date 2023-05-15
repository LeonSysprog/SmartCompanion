#pragma once

#include "../ICommand.h"

class Kill : public ICommand
{
	public:
		void Run() override;
};