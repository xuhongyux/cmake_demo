//
// Created by 夏雨 on 2023/10/11.
//

#include "OpencvConverter.h"

/**
 * 提取帧
 * @param videoPath
 * @param exportPath
 * @param framesPerSecond
 */
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

std::pair<int, int> calculateBoosSite(const std::string &videoPath, const MapStateInfo &mapInfo) {
    // 裁剪
    cv::Mat sourceMat = roiImage(videoPath, mapInfo);
    if (sourceMat.empty()) {
        std::cout << "Error loading image" << std::endl;
        return std::make_pair(0, 0);
    }

    // 2. 将图片从BGR空间转换到HSV空间
    cv::Mat hsv;
    cv::cvtColor(sourceMat, hsv, cv::COLOR_BGR2HSV);

    // 3. 设定红色区域的HSV范围
    cv::Scalar lower_red(0, 120, 70);
    cv::Scalar upper_red(10, 255, 255);
    cv::Scalar lower_red2(170, 120, 70);
    cv::Scalar upper_red2(180, 255, 255);

    // 4. 对HSV图片进行阈值处理，得到红色区域的掩码
    cv::Mat mask1, mask2;
    cv::inRange(hsv, lower_red, upper_red, mask1);
    cv::inRange(hsv, lower_red2, upper_red2, mask2);
    cv::Mat mask = mask1 | mask2;

    // 5. 寻找轮廓
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(mask, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    return calculateRoleSiteIndex(calculateMaxProfile(contours),mapInfo);
}

cv::Mat roiImage(const std::string &videoPath, const MapStateInfo &mapInfo) {
    cv::Mat sourceMat;

    // 1. 读取图片
    cv::Mat src = cv::imread(videoPath);
    if (src.empty()) {
        return sourceMat;
    }
    // 2. 创建ROI
    cv::Rect roi(
            mapInfo.start_x_point,
            mapInfo.start_y_point,
            mapInfo.cell_size * mapInfo.check_row,
            mapInfo.cell_size * mapInfo.check_col);
    return src(roi);
}

std::pair<int, int> calculateMaxProfile(std::vector<vector<Point>> &contours) {
    if (contours.empty()) {
        return std::make_pair(0, 0);
    }
    // 找到面积最大的轮廓
    int largestContourIndex = 0;
    double largestContourArea = 0;
    for (size_t i = 0; i < contours.size(); i++) {
        double area = contourArea(contours[i]);
        if (area > largestContourArea) {
            largestContourArea = area;
            largestContourIndex = i;
        }
    }
    // 计算面积最大轮廓的中心点
    Moments m = moments(contours[largestContourIndex]);
    return std::make_pair(int(m.m10 / m.m00), int(m.m01 / m.m00));
};

/**
 * 计算小人轮廓的索引
 * @param site
 * @param mapInfo
 * @return
 */
std::pair<int, int> calculateRoleSiteIndex(std::pair<int, int> site,const MapStateInfo &mapInfo) {
    int rowIndex = site.first / mapInfo.cell_size + 1;
    int colIndex = site.second / mapInfo.cell_size + 1;
    return std::make_pair(rowIndex, colIndex);
}


std::pair<int, int> calculateRoleSite(const std::string &videoPath, const MapStateInfo &mapInfo) {
    // 裁剪
    cv::Mat sourceMat = roiImage(videoPath, mapInfo);
    if (sourceMat.empty()) {
        std::cout << "Error loading image" << std::endl;
        return std::make_pair(0, 0);
    }
    // 转换颜色空间到 HSV
    cv::Mat hsv;
    cv::cvtColor(sourceMat, hsv, cv::COLOR_BGR2HSV);

    // 对蓝色进行阈值处理
    cv::Mat mask;
    cv::inRange(hsv, cv::Scalar(100, 80, 80), cv::Scalar(130, 255, 255), mask);

    // 查找轮廓
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    return calculateRoleSiteIndex(calculateMaxProfile(contours),mapInfo);
}

void calculateTheMapColourRead(const std::string &videoPath) {
    // 1. 读取图片
    cv::Mat src = cv::imread(videoPath);
    if (src.empty()) {
        std::cout << "Error loading image" << std::endl;
        return;
    }
    // 2. 将图片从BGR空间转换到HSV空间
    cv::Mat hsv;
    cv::cvtColor(src, hsv, cv::COLOR_BGR2HSV);

    // 3. 设定红色区域的HSV范围
    cv::Scalar lower_red(0, 120, 70);
    cv::Scalar upper_red(10, 255, 255);
    cv::Scalar lower_red2(170, 120, 70);
    cv::Scalar upper_red2(180, 255, 255);

    // 4. 对HSV图片进行阈值处理，得到红色区域的掩码
    cv::Mat mask1, mask2;
    cv::inRange(hsv, lower_red, upper_red, mask1);
    cv::inRange(hsv, lower_red2, upper_red2, mask2);
    cv::Mat mask = mask1 | mask2;

    //cv::imshow("mask", mask);


    // 7. 寻找轮廓
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(mask, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // 8. 寻找最大轮廓
    int largestContourIndex = -1;
    double maxArea = 0;
    for (size_t i = 0; i < contours.size(); i++) {
        double area = cv::contourArea(contours[i]);
        if (area > maxArea) {
            maxArea = area;
            largestContourIndex = i;
        }
    }

    // 9. 计算最大轮廓的几何中心
    cv::Point2f center;
    if (largestContourIndex != -1) {
        cv::Moments moments = cv::moments(contours[largestContourIndex]);
        center = cv::Point2f(moments.m10 / moments.m00, moments.m01 / moments.m00);
    } else {
        std::cout << "No red region found" << std::endl;
        return;
    }

    // 10. 输出中心坐标
    std::cout << "Center of red region: (" << center.x << ", " << center.y << ")" << std::endl;



    // cv::imshow("redRegion", redRegion);
    // 7. 显示结果
    //  cv::imshow("Original Image", src);
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

