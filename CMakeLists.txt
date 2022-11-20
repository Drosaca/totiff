cmake_minimum_required(VERSION 3.23)
project(totiff)
set(CMAKE_CXX_STANDARD 20)

find_package(TIFF)
include_directories(classes)

add_executable(totiff src/main.cpp classes/RawImage.cpp classes/RawImage.h classes/Tif.cpp classes/Tif.h classes/Config.cpp classes/Config.h classes/Error.cpp classes/Error.h)

target_link_libraries(totiff ${TIFF_LIBRARIES})
