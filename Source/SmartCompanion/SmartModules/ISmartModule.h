#pragma once

class ISmartModule
{
	public:
		virtual void Initialize() = 0;
		virtual void Run() = 0;
		virtual void Shutdown() = 0;
};