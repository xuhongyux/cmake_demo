cmake_minimum_required(VERSION 3.25)
project(cmake_demo)

set(CMAKE_CXX_STANDARD 17)

# 设置OpenCV的路径
set(Torch_DIR /Users/xiayu/context/libtorch/share/cmake/Torch)
set(OpenCV_DIR /Users/xiayu/context/opencv/build_opencv)

# 查找OpenCV库
find_package(OpenCV REQUIRED)
find_package(Torch REQUIRED)

# 添加可执行文件
add_executable(cmake_demo Main.cpp util/OpencvConverter.cpp include/OpencvConverter.h mode/map/MapStateEnum.cpp mode/map/MapStateEnum.h mode/time/GlobalTimer.cpp mode/time/GlobalTimer.h mode/Common.h)


# 引入.h文件
# 使用使用file命令的GLOB选项来获取文件夹列表,每个文件夹的路径逐个传递给include_directories函数
file(GLOB MODE_INCLUDE_DIRS "./mode/*")
include_directories(${MODE_INCLUDE_DIRS})

include_directories(./include)
include_directories(./mode)


# 引入.h文件 结束



# 链接OpenCV库
target_link_libraries(cmake_demo ${OpenCV_LIBS})

