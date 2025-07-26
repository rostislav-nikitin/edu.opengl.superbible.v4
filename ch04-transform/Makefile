CXXFLAGS := -std=c++23 -I../libs/math3d/include -lGL -lGLU -lglut
#CXXFLAGS := -std=c++23 -I../libs/gltools/include -lGL -lGLU -lglut

all: 10.sphere 20.custom-chip 30.vertex 40.matrix 50.classes


10.sphere:
20.custom-chip:
30.vertex:  30.vertex.cpp math3d
40.matrix:  40.matrix.cpp math3d
50.classes: 50.classes.cpp math3d

math3d: 
	g++ -c ${CXXFLAGS} -o $@ ../libs/math3d/src/math3d.cpp
	#g++ -c ${CXXFLAGS} -o $@ ../libs/gltools/src/math3d.cpp
