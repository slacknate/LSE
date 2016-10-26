cmake_minimum_required(VERSION 2.8)

# Name of project + type of source (C++ = CXX).
project(LSE CXX)

# Stub application to test our code with.
add_subdirectory(debug)

# Tool to generate shader headers from shader source code.
add_subdirectory(sdump)

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

	# gl source files
	src/gl/light.cpp
	src/gl/material.cpp
	src/gl/manager.cpp
	src/gl/model.cpp
	src/gl/object.cpp
	src/gl/primitive.cpp
	src/gl/program.cpp
	src/gl/rectangle.cpp
	src/gl/rectprism.cpp
	src/gl/vertex.cpp
	
	# render surface source files
	src/gui/screen/screen.cpp

	# program window source files
	src/gui/window/base.cpp
	#src/gui/window/mac.cpp
	#src/gui/window/nix.cpp
	src/gui/window/win.cpp
	
	# user input/output source files
	src/io/base.cpp
	#src/io/mac.cpp
	#src/io/nix.cpp
	src/io/win.cpp
	
	# LSE internals source files
	src/lse/defs.cpp
	src/lse/engine.cpp
	src/lse/exception.cpp
	src/lse/globals.cpp
	src/lse/list.cpp
	src/lse/listnode.cpp
	src/lse/logger.cpp
	src/lse/mutex.cpp
	src/lse/object.cpp
	src/lse/semaphore.cpp
	src/lse/signals.cpp
	src/lse/thread.cpp
	src/lse/event/types.cpp
	
	# physics source files
	src/phy/object.cpp
	
	# utility source files
	src/util/time.cpp
	src/util/file.cpp
	src/util/format.cpp
	src/util/math/matrix.cpp
	src/util/math/quaternion.cpp
	src/util/math/vector.cpp
	src/util/terrain/2D.cpp
	src/util/terrain/3D.cpp
	src/util/terrain/interpolate.cpp
)

# Local include directories.
include_directories(include)

# Set compiler flags.
set(CMAKE_C_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++11")

# Binary output.
add_library(lse SHARED ${SOURCES})

# Create our shader headers from shader source code.
add_custom_target(gl_shaders ALL COMMAND sdump "${CMAKE_SOURCE_DIR}/include/gl/shaders")
add_custom_target(screen_shaders ALL COMMAND sdump "${CMAKE_SOURCE_DIR}/include/gui/screen/shaders")

# Specify libraries to link against:
# -lgdi32 -lanl -lglew32 -lopengl32 -lpthread
target_link_libraries(lse anl glew32 opengl32 pthread)

# Executable output is dependent on our shaders being compiled.
add_dependencies(lse gl_shaders)
add_dependencies(lse screen_shaders)

# Shader headers can only be generated if sdump is built.
add_dependencies(gl_shaders sdump)
add_dependencies(screen_shaders sdump)

# Debug program is dependent on the DLL being built.
add_dependencies(debug lse)