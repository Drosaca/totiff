cmake_minimum_required(VERSION 3.22)
project(totiff)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_GENERATOR UNIX MAKEFILE)
find_package(TIFF)
include_directories(classes)

add_executable(totiff src/main.cpp classes/RawImage.cpp classes/RawImage.h classes/Tif.cpp classes/Tif.h classes/Config.cpp classes/Config.h classes/Error.cpp classes/Error.h )

target_link_libraries(totiff ${TIFF_LIBRARIES} )