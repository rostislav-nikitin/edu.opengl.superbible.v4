#include <GL/gli.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <memory>
#include <cmath>

#include <iostream>

static GLfloat constexpr const PI{3.1415};
static GLfloat constexpr const Size{200.0f};
static GLfloat constexpr const da{0.1f/(2.0f * PI)};

static GlImage::GlImage image{GlImage::make_tga_image("./sample_640x426.tga")};
static bool isIncA{true};
static GLfloat a{};

auto setupRc() -> void
{
	glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
}

auto onResizeWindow(GLsizei width, GLsizei heigth) -> void
{
	if (width == 0)
		width = 1;

	glViewport(0, 0, width, heigth);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	GLfloat ratio = GLfloat(width) / GLfloat(heigth);

	if (width < heigth)
		glOrtho(0, Size, 0, Size / ratio, 0, Size);
	else
		glOrtho(0, Size * ratio, 0, Size, 0, Size);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

auto onRenderScene() -> void
{
	GLint viewport[4];
	GLfloat invertMap[256];
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	// Draw scene
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glRasterPos2i(0, 0);

	glGetIntegerv(GL_VIEWPORT, viewport);
	glPixelZoom(GLfloat(viewport[2]) / GLfloat(image.getWidth()), GLfloat(viewport[3]) / GLfloat(image.getHeigth()));

	for (int idx = 0; idx < sizeof(invertMap) / sizeof(GLfloat); ++idx)
		invertMap[idx] = 1.0f / 255.0f * GLfloat(idx) * cosf(a);

	glPixelMapfv(GL_PIXEL_MAP_R_TO_R, 255, invertMap);
	glPixelMapfv(GL_PIXEL_MAP_G_TO_G, 255, invertMap);
	glPixelMapfv(GL_PIXEL_MAP_B_TO_B, 255, invertMap);
	glPixelTransferi(GL_MAP_COLOR, GL_TRUE);

	glDrawPixels(image.getWidth(), image.getHeigth(), image.getFormat(), GL_UNSIGNED_BYTE, image.getContent());

	glPixelTransferi(GL_MAP_COLOR, GL_FALSE);
	glPixelZoom(1.0f, 1.0f);
	glPixelTransferf(GL_RED_SCALE, 1.0f);
	glPixelTransferf(GL_GREEN_SCALE, 1.0f);
	glPixelTransferf(GL_BLUE_SCALE, 1.0f);

	glutSwapBuffers();
}

auto onTimer(int) -> void
{
	if(isIncA)
		a += da;
	else
		a -= da;

	if ((a >= PI / 2.0) || (a <= 0.0f))
		isIncA = !isIncA;
		

	glutPostRedisplay();

	glutTimerFunc(1000 / 60, onTimer, 0);
}

auto main(int argc, char *argv[]) -> int
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	
	glutInitWindowSize(640, 426);
	glutCreateWindow("Draw Pixels Sample");

	setupRc();

	glutReshapeFunc(onResizeWindow);
	glutDisplayFunc(onRenderScene);
	glutTimerFunc(1000 / 60, onTimer, 0);

	glutMainLoop();

	return EXIT_SUCCESS;
}
