cmake_minimum_required(VERSION 3.10)

project(main)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(imgui REQUIRED)

include_directories(include)
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cc")

add_executable(main ${SOURCES})
target_link_libraries(main glfw imgui)