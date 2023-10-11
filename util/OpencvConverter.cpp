//
// Created by 夏雨 on 2023/10/11.
//

#include "../include/OpencvConverter.h"

void extractFrames(const std::string &videoPath, const std::string &exportPath, int framesPerSecond) {
    VideoCapture video(videoPath);

    if (!video.isOpened()) {
        std::cout << "无法打开视频文件" << std::endl;
        return;
    }

    // 总帧数
    int frameCount = video.get(cv::CAP_PROP_FRAME_COUNT);

    // 获取视频帧率
    int frameRate = video.get(cv::CAP_PROP_FPS);


    int skipNumber = (frameCount / frameRate) / framesPerSecond;

    int currentSkip = 0;

    for (int i = 0; i < frameCount; i++) {
        Mat frame;
        video >> frame;
        if (currentSkip < skipNumber) {
            currentSkip++;
            continue;
        }
        currentSkip = 0;

        // 构造保存图像的文件名
        std::string filename = exportPath + "frame_" + std::to_string(i) + ".jpg";

        // 保存帧为图像文件
        cv::imwrite(filename, frame);
    }
    video.release();
    std::cout << "已成功保存图像帧！" << std::endl;
}


void calculateTheMapBlue(const std::string &videoPath) {
    // 1. 读取图片
    cv::Mat src = cv::imread("path/to/your/image.jpg");
    if (src.empty()) {
        std::cout << "Error loading image" << std::endl;
        return ;
    }

    // 2. 转换颜色空间到 HSV
    cv::Mat hsv;
    cv::cvtColor(src, hsv, cv::COLOR_BGR2HSV);

    // 3. 对蓝色进行阈值处理
    cv::Mat mask;
    cv::inRange(hsv, cv::Scalar(100, 100, 100), cv::Scalar(130, 255, 255), mask);

    // 4. 查找轮廓
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // 5. 遍历轮廓并找到中心点
    for (const auto& contour : contours) {
        cv::Moments m = cv::moments(contour);
        int cx = int(m.m10 / m.m00);
        int cy = int(m.m01 / m.m00);

        // 6. 在原图上绘制中心点
        cv::circle(src, cv::Point(cx, cy), 5, cv::Scalar(0, 0, 255), -1);
    }

    // 7. 显示结果
    cv::imshow("Result", src);
    cv::waitKey(0);
}
void calculateTheMap(const std::string &videoPath) {
    // 读取输入的图像文件
    if (videoPath.empty()) {
        cout << "Usage: ./grayscale <image_path>" << endl;
        return;
    }

    Mat image = imread(videoPath, IMREAD_COLOR);
    // 检查图像是否成功读取
    if (image.empty()) {
        cout << "Error: Could not open or find the image." << endl;
        return;
    }

    // 将图像转换为灰度图像
    Mat gray_image;
    cvtColor(image, gray_image, COLOR_BGR2GRAY);

//    // 显示原始图像和灰度图像
//    namedWindow("Original Image", WINDOW_AUTOSIZE);
//    imshow("Original Image", image);
//
//
//    namedWindow("Gray Image", WINDOW_AUTOSIZE);
//    imshow("Gray Image", gray_image);


    // 3. 应用阈值处理以强调深色格子
    cv::Mat thresh;
    cv::threshold(gray_image, thresh, 50, 255, cv::THRESH_BINARY_INV);

    // 4. 使用findContours()函数找到所有格子
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(thresh, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

//    // 5. 计算并打印格子数量和位置
//    std::cout << "Number of squares: " << contours.size() << std::endl;
//    for (size_t i = 0; i < contours.size(); ++i) {
//        cv::Rect boundingRect = cv::boundingRect(contours[i]);
//        std::cout << "Square " << i + 1 << " position: (" << boundingRect.x << ", " << boundingRect.y << ")" << std::endl;
//    }

    // 用红色线画出格子
    for (size_t i = 0; i < contours.size(); ++i) {
        // 可以通过设置条件来筛选轮廓，例如轮廓面积、长宽比等
        // double area = contourArea(contours[i]);
        // if (area < minArea || area > maxArea) continue;

        drawContours(thresh, contours, static_cast<int>(i), cv::Scalar(255, 192, 203), 2, LINE_8, hierarchy, 0);
    }

    // 显示结果
    namedWindow("Result", WINDOW_NORMAL);
    imshow("Result", thresh);

    // 等待按键，然后关闭窗口
    waitKey(0);
    destroyAllWindows();

}

