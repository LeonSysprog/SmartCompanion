#pragma once

class ISmartModule
{
	protected:
		UWorld* worldContext;

	public:
		virtual void	Initialize() = 0;
		virtual void*	Run() = 0;
		virtual void	Shutdown() = 0;
};