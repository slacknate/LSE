cmake_minimum_required(VERSION 2.8)

project(SCREEN_SHADERS)

add_custom_target(screen_shaders ALL sdump "${CMAKE_SOURCE_DIR}/include/gui/screen" "gl_screen")

# This project is dependent on sdump being built.
add_dependencies(screen_shaders sdump)