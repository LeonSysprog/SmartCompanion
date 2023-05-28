#include "ComputerVisionModule.h"
#include "../../SmartCompanionCharacter.h"

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"

#include <vector>
#include <fstream>
#include <cmath>

ComputerVisionModule::ComputerVisionModule()
{
}

ComputerVisionModule::ComputerVisionModule(UWorld* _worldContext)
{
    worldContext = _worldContext;
}

/*
void ComputerVisionModule::preProcess()
{
	cv::Mat blob;
	cv::dnn::blobFromImage(img, blob, 1. / 255., cv::Size(640, 640), cv::Scalar(), true, false);

	primaryModel.setInput(blob);
	outputs = primaryModel.forward();
}

void ComputerVisionModule::postProcess()
{
    // Initialize vectors to hold respective outputs while unwrapping detections.
    std::vector<float> confidences;
    std::vector<cv::Rect> boxes;

    float* data = (float*)outputs.data;
    const int rows = 8400;

    double maxScore;

    for (int i = 0; i < rows; ++i)
    {
        double confidence = data[4];

        if (confidence < 0.25) continue;

        float* classes_scores = data + 5;
        cv::Mat scores(1, 1, CV_32FC1, classes_scores);
        cv::minMaxLoc(scores, nullptr, &maxScore, nullptr, nullptr);

        if (maxScore >= 0.25)
        {
            boxes.push_back({
                int(data[0] - 0.5 * data[2]),
                int(data[1] - 0.5 * data[3]),
                int(data[2]),
                int(data[3]) });

            confidences.push_back(confidence);
        }

        data += 6;
    }

    // Perform Non-Maximum Suppression and draw predictions.
    std::vector<int> indices;
    cv::dnn::NMSBoxes(boxes, confidences, 0.25, 0.45, indices, 0.5);
    for (int i = 0; i < indices.size(); ++i)
    {
        int idx = indices[i];
        cv::Rect box = boxes[idx];
        int left = box.x;
        int top = box.y;
        int width = box.width;
        int height = box.height;

        // Draw bounding box.
        cv::rectangle(img, cv::Point(left, top), cv::Point(left + width, top + height), cv::Scalar(0, 255, 0), 3);
    }
}
*/

float ComputerVisionModule::getRotateAngle(int x0, int y0)
{
    float alpha = atan((xLength / 2 - x0) / y0);
    if (x0 < xLength) alpha *= -1;
    return alpha / PI;
}

void ComputerVisionModule::Initialize()
{
    /*
    * заменить на абсолютные
	redModel = cv::dnn::readNet("..\\..\\..\\..\\ThirdParty\\Models\\OpenCV\\redModel.onnx");
	blueModel = cv::dnn::readNet("..\\..\\..\\..\\ThirdParty\\Models\\OpenCV\\blueModel.onnx");
    */
}

float ComputerVisionModule::Run()
{
	// сделать скриншот и сохранить
    auto controller = UGameplayStatics::GetPlayerController(worldContext, 0);
    auto character = (ASmartCompanionCharacter*)(controller->GetPawn());
    character->ActivateFirstPersonView();

    system("python D:\\SmartCompanion\\SmartCompanion\\Script\\yolov8.py");

    // read coords of center of detected image
    std::ifstream coordsFile("D:\\SmartCompanion\\SmartCompanion\\Script\\coords.txt");
    int x, y;
    coordsFile >> x >> y;
    coordsFile.close();

	return (!x && !y) ? 0 : getRotateAngle(x, y);
}

void ComputerVisionModule::SetPrimaryModel(const std::string& modelName)
{
    //modelName == "red" ? primaryModel = redModel : primaryModel = blueModel;
    UE_LOG(LogTemp, Display, TEXT("SetPrimaryModel"));
}

UWorld* ComputerVisionModule::GetWorldContext()
{
    return worldContext;
}

void ComputerVisionModule::Shutdown()
{
}
