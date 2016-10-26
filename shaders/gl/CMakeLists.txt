cmake_minimum_required(VERSION 2.8)

project(GL_SHADERS)

add_custom_target(gl_shaders ALL sdump "${CMAKE_SOURCE_DIR}/include/gl" "gl_obj")

# This project is dependent on sdump being built.
add_dependencies(gl_shaders sdump)