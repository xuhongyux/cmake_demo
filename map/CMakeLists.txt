cmake_minimum_required(VERSION 3.25)
project(map)

aux_source_directory(./ SRC)
add_library(map STATIC ${SRC})

# 链接OpenCV库
target_link_libraries(map ${OpenCV_LIBS})