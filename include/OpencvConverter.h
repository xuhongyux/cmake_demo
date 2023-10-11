//
// Created by 夏雨 on 2023/10/11.
//

#ifndef CMAKE_DEMO_OPENCVCONVERTER_H
#define CMAKE_DEMO_OPENCVCONVERTER_H

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

class OpencvConverter {

};

void calculateTheMap(const std::string &videoPath);

void extractFrames(const std::string &videoPath, const std::string &exportPath, int framesPerSecond);

#endif //CMAKE_DEMO_OPENCVCONVERTER_H
