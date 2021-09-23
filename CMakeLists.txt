cmake_minimum_required(VERSION 3.20)
project(test)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBAV REQUIRED IMPORTED_TARGET
        libavcodec
        libavdevice
        libavfilter
        libavformat
        libavutil
        libswscale
        )

add_executable(test main.cpp ScreenRecorder.cpp)

target_link_libraries(${PROJECT_NAME}
        PkgConfig::LIBAV
        )

