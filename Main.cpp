#include "Main.h"

#include <iostream>
#include "OpencvConverter.h"
using namespace cv;


void hello() {
    std::cout << "Hello, World!" << std::endl;
}


void ImageThreshold(String str) {
    Mat image = imread(str);

    imshow("test_opencv",image);
    waitKey(1000);
}


int main() {
//
//    String path ="/Users/xiayu/Pictures/影视/《封神第一部：朝歌风云》2023【封神1080P超清国语HD 在线观看】由费翔、李雪健、黄渤、娜然、于适、陈牧驰、此沙、武亚凡、夏雨、袁泉、王洛勇、陈坤等主演；乌….mp4";
//    String path1 ="/Users/xiayu/yolo资源/标准分辨1067_600.mp4";
//    extractFrames(path1,"/Users/xiayu/yolo资源/dnfStandard_jgp/",2);


    calculateTheMap("/Users/xiayu/yolo资源/属性照片/地图属性.jpg");
    return 0;
}
