# need minimum version (2.8 is good)
cmake_minimum_required(VERSION 2.8)

# Name of project + type of source (C++ = CXX)
project(LSE CXX)

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
	# debug main files
	${CMAKE_SOURCE_DIR}/debug/main.cpp
	${CMAKE_SOURCE_DIR}/debug/cam.cpp
	${CMAKE_SOURCE_DIR}/debug/prism.cpp
	
	# gl source files
	${CMAKE_SOURCE_DIR}/src/gl/light.cpp
	${CMAKE_SOURCE_DIR}/src/gl/material.cpp
	${CMAKE_SOURCE_DIR}/src/gl/manager.cpp
	${CMAKE_SOURCE_DIR}/src/gl/model.cpp
	${CMAKE_SOURCE_DIR}/src/gl/object.cpp
	${CMAKE_SOURCE_DIR}/src/gl/primitive.cpp
	${CMAKE_SOURCE_DIR}/src/gl/program.cpp
	${CMAKE_SOURCE_DIR}/src/gl/rectangle.cpp
	${CMAKE_SOURCE_DIR}/src/gl/rectprism.cpp
	${CMAKE_SOURCE_DIR}/src/gl/shaders.cpp
	${CMAKE_SOURCE_DIR}/src/gl/vertex.cpp
	
	# render surface source files
	${CMAKE_SOURCE_DIR}/src/gui/screen/screen.cpp
	${CMAKE_SOURCE_DIR}/src/gui/screen/shaders.cpp
	
	# program window source files
	${CMAKE_SOURCE_DIR}/src/gui/window/base.cpp
	#${CMAKE_SOURCE_DIR}/src/gui/window/mac.cpp
	#${CMAKE_SOURCE_DIR}/src/gui/window/nix.cpp
	${CMAKE_SOURCE_DIR}/src/gui/window/win.cpp
	
	# user input/output source files
	${CMAKE_SOURCE_DIR}/src/io/base.cpp
	#${CMAKE_SOURCE_DIR}/src/io/mac.cpp
	#${CMAKE_SOURCE_DIR}/src/io/nix.cpp
	${CMAKE_SOURCE_DIR}/src/io/win.cpp
	
	# LSE internals source files
	${CMAKE_SOURCE_DIR}/src/lse/defs.cpp
	${CMAKE_SOURCE_DIR}/src/lse/engine.cpp
	${CMAKE_SOURCE_DIR}/src/lse/exception.cpp
	${CMAKE_SOURCE_DIR}/src/lse/globals.cpp
	${CMAKE_SOURCE_DIR}/src/lse/list.cpp
	${CMAKE_SOURCE_DIR}/src/lse/listnode.cpp
	${CMAKE_SOURCE_DIR}/src/lse/logger.cpp
	${CMAKE_SOURCE_DIR}/src/lse/mutex.cpp
	${CMAKE_SOURCE_DIR}/src/lse/object.cpp
	${CMAKE_SOURCE_DIR}/src/lse/semaphore.cpp
	${CMAKE_SOURCE_DIR}/src/lse/signals.cpp
	${CMAKE_SOURCE_DIR}/src/lse/thread.cpp
	${CMAKE_SOURCE_DIR}/src/lse/event/types.cpp
	
	# physics source files
	${CMAKE_SOURCE_DIR}/src/phy/object.cpp
	
	# utility source files
	${CMAKE_SOURCE_DIR}/src/util/time.cpp
	${CMAKE_SOURCE_DIR}/src/util/format.cpp
	# ${CMAKE_SOURCE_DIR}/src/util/math/matrix.cpp
	${CMAKE_SOURCE_DIR}/src/util/math/quaternion.cpp
	${CMAKE_SOURCE_DIR}/src/util/math/vector.cpp
	${CMAKE_SOURCE_DIR}/src/util/terrain/2D.cpp
	${CMAKE_SOURCE_DIR}/src/util/terrain/3D.cpp
	${CMAKE_SOURCE_DIR}/src/util/terrain/interpolate.cpp
	)
	
# need where to include stuff from.
include_directories(
	${CMAKE_SOURCE_DIR}/include
	${CMAKE_SOURCE_DIR}/debug
)

# now let's do some compiler flags
set(CMAKE_C_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++11")

# now let's make an executable
add_executable(lse ${SOURCES})

# ok, it needs to link against some libraries
# -lgdi32 -lanl -lglew32 -lopengl32 -lpthread
target_link_libraries(lse anl glew32 opengl32 pthread)