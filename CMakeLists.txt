cmake_minimum_required(VERSION 4.1)
project(chare C)

set(CMAKE_C_STANDARD 17)

add_executable(chare src/main.c
        src/network.c
        src/http.c
        include/http.h
        include/network.h
        include/platform_io.h
        src/platform_io.c)

target_include_directories(chare PRIVATE include)
