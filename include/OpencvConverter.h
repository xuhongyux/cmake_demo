//
// Created by 夏雨 on 2023/10/11.
//

#ifndef CMAKE_DEMO_OPENCVCONVERTER_H
#define CMAKE_DEMO_OPENCVCONVERTER_H

#include <opencv2/opencv.hpp>
#include <iostream>
#include "MapStateEnum.h"

using namespace cv;
using namespace std;

class OpencvConverter {

};

void calculateTheMap(const std::string &videoPath);

void extractFrames(const std::string &videoPath, const std::string &exportPath, int framesPerSecond);

/**
 * 计算角色位置(蓝色)
 * @param videoPath
 * @param mapInfo
 * @return
 */
std::pair<int, int> calculateRoleSite(const std::string &videoPath,const MapStateInfo& mapInfo);



/**
 * 计算boss位置(红色)
 * @param videoPath
 * @param mapInfo
 * @return
 */
std::pair<int, int> calculateBoosSite(const std::string &videoPath, const MapStateInfo &mapInfo);


/**
 * 计算地图颜色域  测试用
 * @param videoPath
 */
void calculateTheMapColourRead(const std::string &videoPath);


/**
 * 计算角色位置坐标位置(0,0)
 * @param site
 * @param mapInfo
 * @return
 */
std::pair<int, int> calculateRoleSiteIndex(std::pair<int, int> site,const MapStateInfo &mapInfo);


/**
 * 计算最大轮廓位置
 * @param contours
 * @return
 */
std::pair<int, int> calculateMaxProfile(std::vector<vector<Point>> &contours);


/**
 * 地图裁剪
 * @param videoPath
 * @param mapInfo
 * @return
 */
cv::Mat roiImage(const std::string &videoPath, const MapStateInfo &mapInfo);


#endif //CMAKE_DEMO_OPENCVCONVERTER_H
