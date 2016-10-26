cmake_minimum_required(VERSION 2.8)

project(SDUMP C)

set(SOURCES main.c)

set(CMAKE_C_FLAGS "-Wall -Wextra")

add_executable(sdump ${SOURCES})
