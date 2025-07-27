CXXFLAGS+=-std=c++23 -I../libs/math3d/include -I../libs/gl_image/include -I../libs/glad/include -lEGL -lGL -lGLU -lglut

all:10.bitmaps 20.draw-pixels 30.translation 40.imaging-subset

10.bitmaps:
20.draw-pixels:libglimage.a
30.translation:libglimage.a
40.imaging-subset:libglimage.a libglad.a

libglad.a:glad
	ar rcs $@ $^

glad:
	g++ -c ${CXXFLAGS} -o $@ ../libs/glad/src/glad.c

libglimage.a:helpers tga_image gl_image gli
	ar rcs $@ $^
#	rm $^

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

