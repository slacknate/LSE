cmake_minimum_required(VERSION 2.8)

project(SDUMP C)

set(SOURCES src/main.c)

add_executable(sdump ${SOURCES})

# SDUMP sub-project needs to be built before LSE
# add_dependencies(lse SDUMP)
