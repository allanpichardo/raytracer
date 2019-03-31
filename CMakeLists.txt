cmake_minimum_required(VERSION 3.13)
project(raytracer)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

add_executable(raytracer main.cpp headers/Camera.h headers/Plane.h headers/Sphere.h headers/Mesh.h headers/Light.h impl/Camera.cpp impl/Plane.cpp impl/Sphere.cpp impl/Mesh.cpp impl/Light.cpp headers/Cimg.h)

find_package(glm REQUIRED)

target_include_directories(raytracer PUBLIC ${GLM_INCLUDE_DIRS} PRIVATE headers)

target_link_libraries(raytracer ${GLM_LIBRARY})