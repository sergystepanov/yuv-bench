cmake_minimum_required(VERSION 3.16)
project(yuv_bench C)

set(CMAKE_C_STANDARD 11)

add_executable(yuv_bench main.c image/gen.c image/gen.h conv/conv.c conv/conv.h tui/term.c tui/term.h)

target_link_libraries(yuv_bench -lm)