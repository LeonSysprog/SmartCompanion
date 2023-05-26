#include "ComputerVisionModule.h"
#include "../../SmartCompanionCharacter.h"

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"

#include <vector>
#include <fstream>

ComputerVisionModule::ComputerVisionModule()
{
}

ComputerVisionModule::ComputerVisionModule(UWorld* _worldContext)
{
    worldContext = _worldContext;
}

/*
void ComputerVisionModule::preProcess(cv::dnn::Net& net)
{
	cv::Mat blob;
	cv::dnn::blobFromImage(img, blob, 1. / 255., cv::Size(640, 640), cv::Scalar(), true, false);

	net.setInput(blob);
	outputs = net.forward();
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
        std::cout << data[0] << std::endl;
        std::cout << data[1] << std::endl;
        std::cout << data[2] << std::endl;
        std::cout << data[3] << std::endl;
        std::cout << data[4] << std::endl;
        std::cout << std::endl;

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

float ComputerVisionModule::getRotateAngle()
{
	return 0.0f;
}

void ComputerVisionModule::Initialize()
{
    /*
	redModel = cv::dnn::readNet("..\\..\\..\\..\\ThirdParty\\Models\\OpenCV\\yolov8_custom.onnx");
	blueModel = cv::dnn::readNet("..\\..\\..\\..\\ThirdParty\\Models\\OpenCV\\yolov8_custom.onnx");
    */
}

float ComputerVisionModule::Run()
{
	// сделать скриншот и сохранить
	//preProcess();
	//postProcess();

    UE_LOG(LogTemp, Log, TEXT("ComputerVisionModule::Run()"));

    auto controller = UGameplayStatics::GetPlayerController(worldContext, 0);
    auto character = (ASmartCompanionCharacter*)(controller->GetPawn());
    character->ActivateFirstPersonView();

    system("python D:\\SmartCompanion\\SmartCompanion\\Script\\yolov8.py");
    UE_LOG(LogTemp, Log, TEXT("python script"));

    // read coords of center of detected image
    std::ifstream coordsFile("D:\\SmartCompanion\\SmartCompanion\\Script\\coords.txt");
    int x, y;
    coordsFile >> x >> y;
    coordsFile.close();

	return (!x && !y) ? 0 : 1;
}

void ComputerVisionModule::Shutdown()
{
}

/*
void ComputerVisionModule::SetPrimaryModel(const std::string& modelName)
{
    modelName == "red" ? primaryModel = redModel : primaryModel = blueModel;
}
*/
