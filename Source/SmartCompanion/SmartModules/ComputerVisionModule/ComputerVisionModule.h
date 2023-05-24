#pragma once

//#include "../../../../ThirdParty/OpenCV/include/opencv2/opencv.hpp"
#include "../ISmartModule.h"

//#pragma comment(lib, "D:\\SmartCompanion\\SmartCompanion\\ThirdParty\\lib\\opencv_world470.lib")

class ComputerVisionModule : public ISmartModule
{
	/*
	private:
		cv::Mat img;
		cv::dnn::Net redModel, blueModel;
		cv::Mat outputs;

	private:
		void	preProcess(cv::dnn::Net& net);
		void	postProcess();
		float	getRotateAngle();
	*/
	public:
		ComputerVisionModule();
		ComputerVisionModule(UWorld* _worldContext);

		void	Initialize()	override;
		void*	Run()			override;
		void	Shutdown()		override;
};