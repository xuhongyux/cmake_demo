#include "Main.h"

#include <iostream>
#include "OpencvConverter.h"

using namespace cv;


void hello() {
    std::cout << "Hello, World!" << std::endl;
}


void ImageThreshold(String str) {
    Mat image = imread(str);

    imshow("test_opencv", image);
    waitKey(1000);
}

extern const MapStateInfo STANDARD_11_9;


int main() {

    String testImage = "/Users/xiayu/yolo资源/dnfStandard_jgp/frame_1875.jpg";


    std::pair<int, int> boos = calculateBoosSite(testImage, STANDARD_11_9);

    std::cout << "boos site  " << boos.first <<"  |  "   << boos.second << std::endl;

    std::pair<int, int> role = calculateRoleSite(testImage, STANDARD_11_9);

    std::cout << "role site  " << role.first <<"  |  "   << role.second << std::endl;

    return 0;
}
