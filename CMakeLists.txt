cmake_minimum_required(VERSION 3.22)
project(totiff)
set(CMAKE_CXX_STANDARD 20)

if (MSVC)
    set(TIFF_ROOT ${CMAKE_SOURCE_DIR}/deps/windows/libtiff/)
endif ()

find_package(TIFF)
include_directories(classes ${TIFF_INCLUDE_DIRS})

add_executable(totiff src/main.cpp classes/RawImage.cpp classes/RawImage.h classes/Tif.cpp classes/Tif.h classes/Config.cpp classes/Config.h classes/Error.cpp classes/Error.h)

target_link_libraries(totiff ${TIFF_LIBRARIES})

if (MSVC)
    message(MSVC COMPILER)
    message("LIBRARY:" ${TIFF_LIBRARIES} ${TIFF_INCLUDE_DIRS})
    target_compile_options(totiff PUBLIC /MT)

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