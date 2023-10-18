cmake_minimum_required(VERSION 3.25)
project(roleSite)

aux_source_directory(./ SRC)
add_library(roleSite STATIC ${SRC})

# 链接OpenCV库
target_link_libraries(roleSite ${OpenCV_LIBS})