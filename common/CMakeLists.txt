cmake_minimum_required(VERSION 3.25)
project(common)

aux_source_directory(./ SRC)
add_library(common STATIC ${SRC})

# 链接OpenCV库
target_link_libraries(common ${OpenCV_LIBS})
