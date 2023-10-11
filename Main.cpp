#include "Main.h"

#include <iostream>
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
    String str = "/Users/xiayu/Pictures/简历资源/执行动作.png";
    ImageThreshold(str);
    return 0;
}
