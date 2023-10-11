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
add_executable(cmake_demo Main.cpp)


# 链接OpenCV库
target_link_libraries(cmake_demo ${OpenCV_LIBS})
