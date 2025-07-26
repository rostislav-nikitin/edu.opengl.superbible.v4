#include <GL/gli.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <memory>

#include <iostream>

enum MenuCommand
{
	DrawPixels = 0,
	FlipPixels,
	ZoomPixels,
	JustRedChannel,
	JustGreenChannel,
	JustBlueChannel,
	BlackWhite,
	InvertColors,
};

static GLfloat constexpr const Size{200.0f};

static GlImage::GlImage image{GlImage::make_tga_image("./sample_640x426.tga")};

static MenuCommand command;

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
	bool isModified{false};
	GLint viewport[4];
	std::unique_ptr<char[]> modified = std::make_unique<char[]>(image.getWidth() * image.getHeigth());
	GLfloat invertMap[256];
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	// Draw scene
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glRasterPos2i(0, 0);

	switch(command)
	{
		case DrawPixels:
			break;
		case FlipPixels:
			glPixelZoom(-1.0f, -1.0f);
			glRasterPos2i(Size, Size);
			break;
		case ZoomPixels:
			glGetIntegerv(GL_VIEWPORT, viewport);
			glPixelZoom(GLfloat(viewport[2]) / GLfloat(image.getWidth()), GLfloat(viewport[3]) / GLfloat(image.getHeigth()));
			break;
		case JustRedChannel:
			glPixelTransferf(GL_RED_SCALE, 1.0f);
			glPixelTransferf(GL_GREEN_SCALE, 0.0f);
			glPixelTransferf(GL_BLUE_SCALE, 0.0f);
			break;
		case JustGreenChannel:
			glPixelTransferf(GL_RED_SCALE, 0.0f);
			glPixelTransferf(GL_GREEN_SCALE, 1.0f);
			glPixelTransferf(GL_BLUE_SCALE, 0.0f);
			break;
		case JustBlueChannel:
			glPixelTransferf(GL_RED_SCALE, 0.0f);
			glPixelTransferf(GL_GREEN_SCALE, 0.0f);
			glPixelTransferf(GL_BLUE_SCALE, 1.0f);
			break;
		case BlackWhite:
			glDrawPixels(image.getWidth(), image.getHeigth(), image.getFormat(), GL_UNSIGNED_BYTE, image.getContent());
			glPixelTransferf(GL_RED_SCALE, 0.3f);
			glPixelTransferf(GL_GREEN_SCALE, 0.59f);
			glPixelTransferf(GL_BLUE_SCALE, 0.11f);
			glReadPixels(0, 0, image.getWidth(), image.getHeigth(), GL_LUMINANCE, GL_UNSIGNED_BYTE, modified.get());
/*
			for(int idx = 0; idx < image.getWidth() * image.getHeigth(); ++ idx)
				std::cout << modified.get()[idx];
*/
			glPixelTransferf(GL_RED_SCALE, 1.0f);
			glPixelTransferf(GL_GREEN_SCALE, 1.0f);
			glPixelTransferf(GL_BLUE_SCALE, 1.0f);
			isModified = true;
			break;
		case InvertColors:
			for (int idx = 0; idx < sizeof(invertMap) / sizeof(GLfloat); ++idx)
				invertMap[idx] = 1.0f - 1.0f / 255.0f * GLfloat(idx);

			glPixelMapfv(GL_PIXEL_MAP_R_TO_R, 255, invertMap);
			glPixelMapfv(GL_PIXEL_MAP_G_TO_G, 255, invertMap);
			glPixelMapfv(GL_PIXEL_MAP_B_TO_B, 255, invertMap);
			glPixelTransferi(GL_MAP_COLOR, GL_TRUE);
			break;
	}

	if(!isModified)
		glDrawPixels(image.getWidth(), image.getHeigth(), image.getFormat(), GL_UNSIGNED_BYTE, image.getContent());
	else
		glDrawPixels(image.getWidth(), image.getHeigth(), GL_LUMINANCE, GL_UNSIGNED_BYTE, modified.get());

	glPixelTransferi(GL_MAP_COLOR, GL_FALSE);
	glPixelZoom(1.0f, 1.0f);
	glPixelTransferf(GL_RED_SCALE, 1.0f);
	glPixelTransferf(GL_GREEN_SCALE, 1.0f);
	glPixelTransferf(GL_BLUE_SCALE, 1.0f);

	// Copy
	//glRasterPos2i(image.getWidth() / 2, image.getHeigth() / 2);
	glRasterPos2i(Size / 2, Size / 2);

	glCopyPixels(0, 0, image.getWidth() / 2, image.getHeigth() / 2, GL_COLOR);

	glutSwapBuffers();
}

auto ProcessMenu(int value) -> void
{
	command = static_cast<MenuCommand>(value);

	glutPostRedisplay();
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

	glutCreateMenu(ProcessMenu);
	glutAddMenuEntry(" Draw Pixels ", DrawPixels);
	glutAddMenuEntry(" Flip Pixels ", FlipPixels);
	glutAddMenuEntry(" Zoom Pixels ", ZoomPixels);
	glutAddMenuEntry(" Just Red Channel ", JustRedChannel);
	glutAddMenuEntry(" Just Green Channel ", JustGreenChannel);
	glutAddMenuEntry(" Just Blue Channel ", JustBlueChannel);
	glutAddMenuEntry(" Black & White ", BlackWhite);
	glutAddMenuEntry(" Invert Colors ", InvertColors);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();

	return EXIT_SUCCESS;
}
