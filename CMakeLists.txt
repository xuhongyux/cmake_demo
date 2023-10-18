cmake_minimum_required(VERSION 3.25)
project(cmake_demo)


# 指定c++的标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD 11)

# 设置OpenCV的路径
set(Torch_DIR /Users/xiayu/context/libtorch/share/cmake/Torch)
set(OpenCV_DIR /Users/xiayu/context/opencv/build_opencv)

# 查找OpenCV库
find_package(OpenCV REQUIRED)
find_package(Torch REQUIRED)


# 在根节点处理头文件
include_directories(${PROJECT_SOURCE_DIR}/common)
include_directories(${PROJECT_SOURCE_DIR}/map)
include_directories(${PROJECT_SOURCE_DIR}/roleSite)
include_directories(${PROJECT_SOURCE_DIR}/time)
include_directories(${PROJECT_SOURCE_DIR}/yolov8)



add_subdirectory(common)
add_subdirectory(map)
add_subdirectory(roleSite)
add_subdirectory(time)
add_subdirectory(yolov8)

# 引入子目录的静态库
link_libraries(common map roleSite time yolov8)

# 制作可执行文件
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
add_executable(cmake_demo Main.cpp roleSite/RoleSiteCalculation.cpp roleSite/RoleSiteCalculation.h yolov8/yoloV8Analysis.cpp yolov8/yoloV8Analysis.h)




# 制作库连接 开始

# 添加可执行文件
#file(GLOB_RECURSE SRC_LIST_CPP ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)


# 指定库文件的路径
# set(LIBRARY_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH})

## STATIC 静态库
## SHARED 动态
#add_library(cmake_demo STATIC ${SRC_LIST_CPP})

# 制作库连接 结束

