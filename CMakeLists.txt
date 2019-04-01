cmake_minimum_required(VERSION 3.13)
project(raytracer)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

add_executable(raytracer main.cpp headers/Camera.h headers/Plane.h headers/Sphere.h headers/Mesh.h headers/Light.h impl/Camera.cpp impl/Plane.cpp impl/Sphere.cpp impl/Mesh.cpp impl/Light.cpp headers/Cimg.h headers/Scene.h impl/Scene.cpp headers/SceneObject.h headers/Ray.h impl/Ray.cpp headers/Pixel.h impl/Pixel.cpp impl/Intersection.cpp headers/Intersection.h)

find_package(glm REQUIRED Boost COMPONENTS regex filesystem)

target_include_directories(raytracer PUBLIC ${GLM_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS} PRIVATE headers)

target_link_libraries(raytracer ${GLM_LIBRARY} ${Boost_LIBRARIES})

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)