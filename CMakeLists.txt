cmake_minimum_required(VERSION 3.25)
project(cmake_demo)

set(CMAKE_CXX_STANDARD 17)

# 设置OpenCV的路径
set(Torch_DIR /Users/xiayu/context/libtorch/share/cmake/Torch)
set(OpenCV_DIR /Users/xiayu/context/opencv/build_opencv)

# 查找OpenCV库
find_package(OpenCV REQUIRED)
find_package(Torch REQUIRED)

# 指定c++的标准
set(CMAKE_CXX_STANDARD 11)


# 指定头文件路径
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# 添加可执行文件
file(GLOB_RECURSE SRC_LIST_CPP ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)


# 制作可执行文件

# 指定生成的路径(绝对路径)路径不存在,cmake会帮我们创建
set(HOME /Users/idea_code/cpp/cmake_demo)
set(EXECUTABLE_OUTPUT_PATH ${HOME}/bin)

add_executable(cmake_demo ${SRC_LIST_CPP})

# 制作库连接

# 指定库文件的路径
set(LIBRARY_OUTPUT_PATH ${HOME}/bin)

## STATIC 静态库
## SHARED 动态
#add_library(cmake_demo STATIC ${SRC_LIST_CPP})



# 链接OpenCV库
target_link_libraries(cmake_demo ${OpenCV_LIBS})
