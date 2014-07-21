CPP  = g++.exe
CC   = gcc.exe
WINDRES = windres.exe
RES  = 
OBJ = ../../obj/debug/main.o ../../obj/debug/cam.o ../../obj/debug/prism.o ../../obj/gl/light.o ../../obj/gl/material.o ../../obj/gl/model.o ../../obj/gl/object.o ../../obj/gl/primitive.o  ../../obj/gl/program.o ../../obj/gl/rectangle.o ../../obj/gl/rectprism.o ../../obj/gl/shaders.o ../../obj/gl/vertex.o ../../obj/gui/screen/screen.o ../../obj/gui/screen/shaders.o ../../obj/gui/window/base.o ../../obj/gui/window/win.o ../../obj/io/base.o ../../obj/io/win.o ../../obj/lse/defs.o ../../obj/lse/event.o ../../obj/lse/logger.o ../../obj/lse/listnode.o ../../obj/lse/list.o ../../obj/lse/globals.o ../../obj/lse/engine.o ../../obj/lse/exception.o ../../obj/lse/mutex.o ../../obj/lse/semaphore.o ../../obj/lse/signals.o ../../obj/lse/thread.o ../../obj/phy/object.o ../../obj/util/math/quaternion.o ../../obj/util/math/vector.o ../../obj/util/terrain/2D.o ../../obj/util/terrain/3D.o ../../obj/util/terrain/interpolate.o $(RES)
LINKOBJ = ../../obj/debug/main.o ../../obj/debug/cam.o ../../obj/debug/prism.o ../../obj/gl/light.o ../../obj/gl/material.o ../../obj/gl/model.o ../../obj/gl/object.o ../../obj/gl/primitive.o  ../../obj/gl/program.o ../../obj/gl/rectangle.o ../../obj/gl/rectprism.o ../../obj/gl/shaders.o ../../obj/gl/vertex.o ../../obj/gui/screen/screen.o ../../obj/gui/screen/shaders.o ../../obj/gui/window/base.o ../../obj/gui/window/win.o ../../obj/io/base.o ../../obj/io/win.o ../../obj/lse/defs.o ../../obj/lse/event.o ../../obj/lse/logger.o ../../obj/lse/listnode.o ../../obj/lse/list.o ../../obj/lse/globals.o ../../obj/lse/engine.o ../../obj/lse/exception.o ../../obj/lse/mutex.o ../../obj/lse/semaphore.o ../../obj/lse/signals.o ../../obj/lse/thread.o ../../obj/phy/object.o ../../obj/util/math/quaternion.o ../../obj/util/math/vector.o ../../obj/util/terrain/2D.o ../../obj/util/terrain/3D.o ../../obj/util/terrain/interpolate.o $(RES)
LIBS =  -L"C:/MinGW/lib" -lgdi32 -lanl -lglew32 -lopengl32 -lpthread  
INCS =  -I"C:/MinGW/include"  -I"../../include" 
CXXINCS =  -I"C:/MinGW/lib/gcc/mingw32/3.4.5/include"  -I"C:/MinGW/include/c++/3.4.5/backward"  -I"C:/MinGW/include/c++/3.4.5/mingw32"  -I"C:/MinGW/include/c++/3.4.5"  -I"C:/MinGW/include"  -I"../../include" 
BIN  = ../../bin/engine.exe
CXXFLAGS = $(CXXINCS) -Wall -Wextra
CFLAGS = $(INCS) -Wall -Wextra
RM = rm -f

.PHONY: all all-before all-after clean clean-custom

all: all-before ../../bin/engine.exe all-after

clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CPP) $(LINKOBJ) -o "..\..\bin\engine.exe" $(LIBS)

../../obj/debug/main.o: ../../debug/main.cpp
	$(CPP) -c ../../debug/main.cpp -o ../../obj/debug/main.o $(CXXFLAGS)

../../obj/debug/cam.o: ../../debug/cam.cpp
	$(CPP) -c ../../debug/cam.cpp -o ../../obj/debug/cam.o $(CXXFLAGS)

../../obj/debug/prism.o: ../../debug/prism.cpp
	$(CPP) -c ../../debug/prism.cpp -o ../../obj/debug/prism.o $(CXXFLAGS)

../../obj/io/win.o: ../../src/io/win.cpp
	$(CPP) -c ../../src/io/win.cpp -o ../../obj/io/win.o $(CXXFLAGS)

../../obj/io/base.o: ../../src/io/base.cpp
	$(CPP) -c ../../src/io/base.cpp -o ../../obj/io/base.o $(CXXFLAGS)

../../obj/gl/light.o: ../../src/gl/light.cpp
	$(CPP) -c ../../src/gl/light.cpp -o ../../obj/gl/light.o $(CXXFLAGS)

../../obj/gl/material.o: ../../src/gl/material.cpp
	$(CPP) -c ../../src/gl/material.cpp -o ../../obj/gl/material.o $(CXXFLAGS)

../../obj/gl/model.o: ../../src/gl/model.cpp
	$(CPP) -c ../../src/gl/model.cpp -o ../../obj/gl/model.o $(CXXFLAGS)

../../obj/gl/object.o: ../../src/gl/object.cpp
	$(CPP) -c ../../src/gl/object.cpp -o ../../obj/gl/object.o $(CXXFLAGS)

../../obj/gl/primitive.o: ../../src/gl/primitive.cpp
	$(CPP) -c ../../src/gl/primitive.cpp -o ../../obj/gl/primitive.o $(CXXFLAGS)

../../obj/gl/program.o: ../../src/gl/program.cpp
	$(CPP) -c ../../src/gl/program.cpp -o ../../obj/gl/program.o $(CXXFLAGS)

../../obj/gl/rectangle.o: ../../src/gl/rectangle.cpp
	$(CPP) -c ../../src/gl/rectangle.cpp -o ../../obj/gl/rectangle.o $(CXXFLAGS)

../../obj/gl/rectprism.o: ../../src/gl/rectprism.cpp
	$(CPP) -c ../../src/gl/rectprism.cpp -o ../../obj/gl/rectprism.o $(CXXFLAGS)

../../obj/gl/shaders.o: ../../src/gl/shaders.cpp
	$(CPP) -c ../../src/gl/shaders.cpp -o ../../obj/gl/shaders.o $(CXXFLAGS)

../../obj/gl/vertex.o: ../../src/gl/vertex.cpp
	$(CPP) -c ../../src/gl/vertex.cpp -o ../../obj/gl/vertex.o $(CXXFLAGS)

../../obj/gui/screen/screen.o: ../../src/gui/screen/screen.cpp
	$(CPP) -c ../../src/gui/screen/screen.cpp -o ../../obj/gui/screen/screen.o $(CXXFLAGS)

../../obj/gui/screen/shaders.o: ../../src/gui/screen/shaders.cpp
	$(CPP) -c ../../src/gui/screen/shaders.cpp -o ../../obj/gui/screen/shaders.o $(CXXFLAGS)

../../obj/gui/window/base.o: ../../src/gui/window/base.cpp
	$(CPP) -c ../../src/gui/window/base.cpp -o ../../obj/gui/window/base.o $(CXXFLAGS)

../../obj/gui/window/win.o: ../../src/gui/window/win.cpp
	$(CPP) -c ../../src/gui/window/win.cpp -o ../../obj/gui/window/win.o $(CXXFLAGS)

../../obj/lse/defs.o: ../../src/lse/defs.cpp
	$(CPP) -c ../../src/lse/defs.cpp -o ../../obj/lse/defs.o $(CXXFLAGS)
	
../../obj/lse/event.o: ../../src/lse/event.cpp
	$(CPP) -c ../../src/lse/event.cpp -o ../../obj/lse/event.o $(CXXFLAGS)
	
../../obj/lse/logger.o: ../../src/lse/logger.cpp
	$(CPP) -c ../../src/lse/logger.cpp -o ../../obj/lse/logger.o $(CXXFLAGS)

../../obj/lse/listnode.o: ../../src/lse/listnode.cpp
	$(CPP) -c ../../src/lse/listnode.cpp -o ../../obj/lse/listnode.o $(CXXFLAGS)

../../obj/lse/list.o: ../../src/lse/list.cpp
	$(CPP) -c ../../src/lse/list.cpp -o ../../obj/lse/list.o $(CXXFLAGS)

../../obj/lse/globals.o: ../../src/lse/globals.cpp
	$(CPP) -c ../../src/lse/globals.cpp -o ../../obj/lse/globals.o $(CXXFLAGS)

../../obj/lse/engine.o: ../../src/lse/engine.cpp
	$(CPP) -c ../../src/lse/engine.cpp -o ../../obj/lse/engine.o $(CXXFLAGS)

../../obj/lse/exception.o: ../../src/lse/exception.cpp
	$(CPP) -c ../../src/lse/exception.cpp -o ../../obj/lse/exception.o $(CXXFLAGS)

../../obj/lse/mutex.o: ../../src/lse/mutex.cpp
	$(CPP) -c ../../src/lse/mutex.cpp -o ../../obj/lse/mutex.o $(CXXFLAGS)

../../obj/lse/semaphore.o: ../../src/lse/semaphore.cpp
	$(CPP) -c ../../src/lse/semaphore.cpp -o ../../obj/lse/semaphore.o $(CXXFLAGS)

../../obj/lse/signals.o: ../../src/lse/signals.cpp
	$(CPP) -c ../../src/lse/signals.cpp -o ../../obj/lse/signals.o $(CXXFLAGS)

../../obj/lse/thread.o: ../../src/lse/thread.cpp
	$(CPP) -c ../../src/lse/thread.cpp -o ../../obj/lse/thread.o $(CXXFLAGS)

../../obj/phy/object.o: ../../src/phy/object.cpp
	$(CPP) -c ../../src/phy/object.cpp -o ../../obj/phy/object.o $(CXXFLAGS)

../../obj/util/math/matrix.o: ../../src/util/math/matrix.cpp
	$(CPP) -c ../../src/util/math/matrix.cpp -o ../../obj/util/math/matrix.o $(CXXFLAGS)

../../obj/util/math/quaternion.o: ../../src/util/math/quaternion.cpp
	$(CPP) -c ../../src/util/math/quaternion.cpp -o ../../obj/util/math/quaternion.o $(CXXFLAGS)

../../obj/util/math/vector.o: ../../src/util/math/vector.cpp
	$(CPP) -c ../../src/util/math/vector.cpp -o ../../obj/util/math/vector.o $(CXXFLAGS)

../../obj/util/terrain/2D.o: ../../src/util/terrain/2D.cpp
	$(CPP) -c ../../src/util/terrain/2D.cpp -o ../../obj/util/terrain/2D.o $(CXXFLAGS)

../../obj/util/terrain/3D.o: ../../src/util/terrain/3D.cpp
	$(CPP) -c ../../src/util/terrain/3D.cpp -o ../../obj/util/terrain/3D.o $(CXXFLAGS)

../../obj/util/terrain/interpolate.o: ../../src/util/terrain/interpolate.cpp
	$(CPP) -c ../../src/util/terrain/interpolate.cpp -o ../../obj/util/terrain/interpolate.o $(CXXFLAGS)
