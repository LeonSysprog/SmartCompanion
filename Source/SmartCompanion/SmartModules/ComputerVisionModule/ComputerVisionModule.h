#pragma once

//#include "../../../../ThirdParty/OpenCV/include/opencv2/opencv.hpp"
#include "../ISmartModule.h"

#include <string>

//#pragma comment(lib, "D:\\SmartCompanion\\SmartCompanion\\ThirdParty\\lib\\opencv_world470.lib")

class ComputerVisionModule : public ISmartModule
{
	/*
	private:
		cv::Mat img;
		cv::dnn::Net redModel, blueModel;
		cv::dnn::Net primaryModel;
		cv::Mat outputs;

	private:
		void	preProcess(cv::dnn::Net& net);
		void	postProcess();
		float	getRotateAngle();
	*/
	private:
		const int xLength = 640;

	private:
		float	getRotateAngle(int x0, int y0);

	public:
		ComputerVisionModule();
		ComputerVisionModule(UWorld* _worldContext);

		void	Initialize()	override;
		void	Shutdown()		override;

		float	Run();

		void SetPrimaryModel(const std::string& modelName);
		UWorld* GetWorldContext();
};