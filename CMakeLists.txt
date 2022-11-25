cmake_minimum_required(VERSION 3.22)
project(totiff)
message(COMPILER: ${CMAKE_CXX_COMPILER_ID})
set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_FIND_DEBUG_MODE TRUE)

if (WIN32)
    set(TIFF_ROOT ${CMAKE_SOURCE_DIR}/deps/windows/libtiff/)
    set(CMAKE_CXX_COMPILER cl)
endif ()

find_package(TIFF)
include_directories(classes ${TIFF_INCLUDE_DIRS})
add_executable(totiff src/main.cpp classes/RawImage.cpp classes/RawImage.h classes/Tif.cpp classes/Tif.h classes/Config.cpp classes/Config.h classes/Error.cpp classes/Error.h)
target_link_libraries(totiff ${TIFF_LIBRARIES})

if (WIN32)
    message("LIBRARY:" ${TIFF_LIBRARIES} ${TIFF_INCLUDE_DIRS})

    if (EXISTS ${CMAKE_CURRENT_BINARY_DIR}/Debug)
        add_custom_command(
                TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/deps/windows/libtiff/lib/tiffd.dll
                ${CMAKE_CURRENT_BINARY_DIR}/Debug/)
    elseif (EXISTS ${CMAKE_CURRENT_BINARY_DIR}/Release)
        add_custom_command(
                TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/deps/windows/libtiff/lib/tiffd.dll
                ${CMAKE_CURRENT_BINARY_DIR}/Release)
    else ()
        add_custom_command(
                TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/deps/windows/libtiff/lib/tiffd.dll
                ${CMAKE_CURRENT_BINARY_DIR})
    endif ()
    install(FILES deps/windows/libtiff/lib/tiffd.dll DESTINATION ${CMAKE_INSTALL_PREFIX})
    install(TARGETS totiff DESTINATION ${CMAKE_INSTALL_PREFIX})
endif ()