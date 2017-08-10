# CMake
cmake_minimum_required(VERSION 2.8)
project(ionNVGameWorks)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

# ionEngine

include_directories("${PROJECT_SOURCE_DIR}/../ionEngine")
include_directories("${PROJECT_SOURCE_DIR}/../ionEngine/Include")
include_directories("${PROJECT_SOURCE_DIR}/../ionEngine/Dependencies")
include_directories("${PROJECT_SOURCE_DIR}/../ionEngine/Dependencies/stb")
include_directories("${PROJECT_SOURCE_DIR}/../ionEngine/Dependencies/tinyformat")
include_directories("${PROJECT_SOURCE_DIR}/../ionEngine/Dependencies/glm")
include_directories("${PROJECT_SOURCE_DIR}/../ionEngine/Dependencies/imgui")
include_directories("${PROJECT_SOURCE_DIR}/../ionEngine/Dependencies/Catch/include")
include_directories("${PROJECT_SOURCE_DIR}/../ionEngine/Dependencies/glad/include")

link_directories("${PROJECT_SOURCE_DIR}/../ionEngine/Build/lib")

file(GLOB SOURCES ionNVGameWorks/HBAO.cpp)
add_library(ionNVGameWorks ${SOURCES})
