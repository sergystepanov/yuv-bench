cmake_minimum_required(VERSION 3.16)
project(yuv_bench C)

set(CMAKE_C_STANDARD 11)

add_executable(yuv_bench main.c gen.c gen.h conv.c conv.h)

target_link_libraries(yuv_bench -lm)