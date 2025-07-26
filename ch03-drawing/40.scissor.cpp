#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <iostream>

GLfloat constexpr const Size{100.0f};
GLsizei swidth{};
GLsizei sheigth{};

void onRenderScene(void)
{
	glEnable(GL_SCISSOR_TEST);

	GLsizei dx = swidth / 8;
	GLsizei dy = sheigth / 8;

	glScissor(0, 0, swidth, sheigth);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glScissor(0 + dx, 0 + dy, swidth - 2 * dx, sheigth - 2 * dy);
	glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT); 

	glScissor(0 + 2 * dx, 0 + 2 * dy, swidth - 4 * dx, sheigth - 4 * dy);
	glClearColor(0.0f, 1.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT); 

	glutSwapBuffers();
}

void onResizeWindow(GLsizei width, GLsizei height)
{
	if(0 == height)
		height = 1;

	swidth = width;
	sheigth = height;

	glViewport(0.0f, 0.0f, width, height);

	GLfloat ratio = GLfloat(width) / GLfloat(height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if(width < height)
		glOrtho(-Size, Size, -Size / ratio, Size / ratio, -Size, Size);
	else
		glOrtho(-Size * ratio, Size * ratio, -Size, Size, -Size, Size);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void setupRc()
{
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	glutCreateWindow("Scissors sample");

	glutReshapeFunc(onResizeWindow);
	glutDisplayFunc(onRenderScene);

	setupRc();

	glutMainLoop();

	return EXIT_SUCCESS;
}
