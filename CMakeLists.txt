cmake_minimum_required(VERSION 3.5.0)
project(v3D)
set(CMAKE_CXX_FLAGS"-std=c++20 -Wall -mwindows -DNOMINMAX")
set(CMAKE_CXX_FLAGS_RELEASE"-O3")
link_directories(${PROJECT_SOURCE_DIR}/lib)
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/lib)
add_executable(v3D src/main.cpp src/v3D.cpp)
target_link_libraries(v3D graphics gdiplus gdi32)