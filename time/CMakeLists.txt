cmake_minimum_required(VERSION 3.25)
project(time)

aux_source_directory(./ SRC)
add_library(time STATIC ${SRC})