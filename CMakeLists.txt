cmake_minimum_required(VERSION 3.16)
#set(CMAKE_C_COMPILER gcc)
#set(CMAKE_CXX_COMPILER g++)
project(totiff VERSION 0.1)
set(CMAKE_CXX_STANDARD 20)
message("COMPILER: ${CMAKE_CXX_COMPILER_ID}")

#set(CMAKE_FIND_DEBUG_MODE TRUE)

if (WIN32)
    set(TIFF_ROOT ${CMAKE_SOURCE_DIR}/deps/windows/libtiff/)
endif ()
find_package(TIFF)
if (WIN32)
    set(TIFF_LIBRARIES ${CMAKE_SOURCE_DIR}/deps/windows/libtiff/lib/tiffd.lib)
    set(TIFF_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/deps/windows/libtiff/include/)
endif ()


include_directories(classes include ${TIFF_INCLUDE_DIRS})
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/classes/*.cpp ${PROJECT_SOURCE_DIR}/src/functions.cpp  )

if (TEST)
    include(FetchContent)
    FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    #set(CMAKE_FIND_DEBUG_MODE TRUE)
    FILE(GLOB TEST_SOURCES ${PROJECT_SOURCE_DIR}/src/test/*.cpp)
    add_executable(totiff ${TEST_SOURCES} ${SOURCES})
    enable_testing()
    target_link_libraries(totiff gtest gtest_main)
else ()
    add_executable(totiff ${SOURCES} ${PROJECT_SOURCE_DIR}/src/main.cpp)
endif()
target_link_libraries(totiff ${TIFF_LIBRARIES} )
add_compile_definitions(totiff VERSION=${CMAKE_PROJECT_VERSION})

if (WIN32)
    message("LIBRARY:" ${TIFF_LIBRARIES} ${TIFF_INCLUDE_DIRS})
    if (MSVC)
        target_compile_options(totiff PUBLIC /MT)
    endif ()
    if (CMAKE_COMPILER_IS_GNUCXX)
        message("APPLY GNU PROPERTIES")
        set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")
    endif()
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