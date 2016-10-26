cmake_minimum_required(VERSION 2.8)

project(DEBUG CXX)

if(WIN32)
add_definitions(-DWIN32=1)
add_definitions(-DUNIX=0)
add_definitions(-DAPPLE=0)
elseif(UNIX AND !APPLE)
add_definitions(-DWIN32=0)
add_definitions(-DUNIX=1)
add_definitions(-DAPPLE=0)
elseif(APPLE AND !UNIX)
add_definitions(-DWIN32=0)
add_definitions(-DUNIX=0)
add_definitions(-DAPPLE=1)
endif()

set(SOURCES

    main.cpp
    cam.cpp
    prism.cpp
)

# Include directories for LSE.
include_directories("${CMAKE_SOURCE_DIR}/include")

set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++11")

add_executable(debug ${SOURCES})

# Copy liblse.dll to our binary directory.
add_custom_command(TARGET debug POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:lse> $<TARGET_FILE_DIR:debug>)

target_link_libraries(debug lse)