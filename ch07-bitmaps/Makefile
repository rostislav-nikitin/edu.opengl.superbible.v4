CXXFLAGS+=-std=c++23 -I../libs/math3d/include -I../libs/gl_image/include -lGL -lGLU -lglut

all:10.bitmaps 20.draw-pixels

10.bitmaps:
20.draw-pixels:libglimage.a

libglimage.a:helpers tga_image gl_image gli
	ar rcs $@ $^

helpers:
	g++ -c ${CXXFLAGS} -o $@ ../libs/gl_image/src/helpers.cpp

tga_image:
	g++ -c ${CXXFLAGS} -o $@ ../libs/gl_image/src/tga_image.cpp

gl_image:
	g++ -c ${CXXFLAGS} -o $@ ../libs/gl_image/src/gl_image.cpp

gli:
	g++ -c ${CXXFLAGS} -o $@ ../libs/gl_image/src/gli.cpp

math3d:
	g++ -c ${CXXFLAGS} -o $@ ../libs/math3d/src/math3d.cpp

