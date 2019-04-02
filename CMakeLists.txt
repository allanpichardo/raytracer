cmake_minimum_required(VERSION 3.13)
project(raytracer)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

##############################################
## External libraries
##############################################
list( APPEND CMAKE_MODULE_PATH
        ${PROJECT_SOURCE_DIR}/extern
        )

add_executable(raytracer main.cpp headers/Camera.h headers/Plane.h headers/Sphere.h headers/Mesh.h headers/Light.h implementation/Camera.cpp implementation/Plane.cpp implementation/Sphere.cpp implementation/Mesh.cpp implementation/Light.cpp headers/Scene.h implementation/Scene.cpp headers/SceneObject.h headers/Ray.h implementation/Ray.cpp headers/Pixel.h implementation/Pixel.cpp implementation/Intersection.cpp headers/Intersection.h implementation/Loader.cpp headers/Loader.h)

find_package(CImg REQUIRED glm REQUIRED Boost COMPONENTS regex filesystem)


target_include_directories(raytracer PUBLIC ${GLM_INCLUDE_DIRS} ${CImg_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS} PRIVATE headers)
#target_link_directories(raytracer ${CImg_SYSTEM_LIBS_DIR})
target_link_libraries(raytracer ${GLM_LIBRARY} ${CImg_SYSTEM_LIBS} ${Boost_LIBRARIES})

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

# CImg
#find_package( CImg REQUIRED )
#list( APPEND PROJ_INCLUDE_DIRS
#        ${CImg_INCLUDE_DIRS}
#        )
#list( APPEND
#        PROJ_LIBRARY_DIRS
#        ${CImg_SYSTEM_LIBS_DIR}
#        )

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CIMG_CFLAGS}")

