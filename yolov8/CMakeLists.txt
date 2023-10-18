cmake_minimum_required(VERSION 3.25)
project(yolov8)

aux_source_directory(./ SRC)


file(GLOB_RECURSE SRCH ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
set(ALL_SRC ${SRCH} ${SRC})

# include_directories(/Users/xiayu/context/lib/yolov8)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/yolov8/include)

# ONNXRUNTIME

link_directories(/Users/xiayu/context/onnxruntime-osx-arm64-1.16.1/lib/libonnxruntime.dylib)
include_directories(${PROJECT_NAME} /Users/xiayu/context/onnxruntime-osx-arm64-1.16.1/include)

# ! ONNXRUNTIME

add_library(yolov8 STATIC ${ALL_SRC})

# 链接OpenCV库
target_link_libraries(yolov8 ${OpenCV_LIBS})
target_link_libraries(yolov8 /Users/xiayu/context/onnxruntime-osx-arm64-1.16.1/lib/libonnxruntime.dylib)
