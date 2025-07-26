#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <math3d/math3d.h>

#include <iostream>

static GLfloat constexpr const Size{100.0f};

static GLfloat cubeY{0.0f};

auto onResizeWindow(GLsizei width, GLsizei heigth) -> void
{
	if(heigth == 0)
		heigth = 1;

	glViewport(0, 0, width, heigth);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	GLfloat ratio = GLfloat(width) / GLfloat(heigth);

	if(width < heigth)
		glOrtho(-Size, Size, -Size / ratio, Size / ratio, -Size, Size);
	else
		glOrtho(-Size * ratio, Size * ratio, -Size, Size, -Size, Size);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

auto drawCoordinates() -> void
{
	glBegin(GL_LINES);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-Size, 0.0f, 0.0f);
		glVertex3f( Size, 0.0f, 0.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, -Size, 0.0f);
		glVertex3f(0.0f,  Size, 0.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, -Size);
		glVertex3f(0.0f, 0.0f,  Size);
	glEnd();
}

auto drawCube() -> void
{
	GLfloat constexpr const HalfSideSize{Size / 4};
	glBegin(GL_TRIANGLE_STRIP);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-HalfSideSize, -HalfSideSize,  HalfSideSize);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-HalfSideSize, -HalfSideSize, -HalfSideSize);
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f( HalfSideSize, -HalfSideSize,  HalfSideSize);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f( HalfSideSize, -HalfSideSize, -HalfSideSize);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(HalfSideSize,  HalfSideSize, -HalfSideSize);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(HalfSideSize,  HalfSideSize,  HalfSideSize);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(HalfSideSize, -HalfSideSize, -HalfSideSize);
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(HalfSideSize, -HalfSideSize,  HalfSideSize);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-HalfSideSize, -HalfSideSize, -HalfSideSize);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-HalfSideSize,  HalfSideSize, -HalfSideSize);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f( HalfSideSize, -HalfSideSize, -HalfSideSize);
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f( HalfSideSize,  HalfSideSize, -HalfSideSize);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(-HalfSideSize, HalfSideSize,  HalfSideSize);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f( HalfSideSize, HalfSideSize,  HalfSideSize);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-HalfSideSize, HalfSideSize, -HalfSideSize);
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f( HalfSideSize, HalfSideSize, -HalfSideSize);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-HalfSideSize,  HalfSideSize, -HalfSideSize);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-HalfSideSize, -HalfSideSize, -HalfSideSize);
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(-HalfSideSize,  HalfSideSize,  HalfSideSize);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-HalfSideSize, -HalfSideSize,  HalfSideSize);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-HalfSideSize, -HalfSideSize, HalfSideSize);
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f( HalfSideSize, -HalfSideSize, HalfSideSize);
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(-HalfSideSize,  HalfSideSize, HalfSideSize);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f( HalfSideSize,  HalfSideSize, HalfSideSize);
	glEnd();
}

auto onRenderScene() -> void
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

		glTranslatef(0.0f, 0.0f, -25.0f);
		glRotatef(41.25, 1.0f, 0.0f, 0.0f);
		glRotatef(-22.5, 0.0f, 1.0f, 0.0f);

		drawCoordinates();

		glRotatef(cubeY, 0.0f, 1.0f, 0.0f);

		drawCube();

	glPopMatrix();

	glutSwapBuffers();
}

auto onTimer(int) -> void
{
	cubeY += 1.0f;
	if(cubeY >= 360.0f)
		cubeY = 0.0f;

	glutTimerFunc(1000 / 60, onTimer, 0);
	glutPostRedisplay();
}

auto setupRc() -> void
{
	glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
	//glShadeModel(GL_SHADER);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);
	glEnable(GL_CULL_FACE);
}

auto main(int argc, char *argv[]) -> int
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);

	glutCreateWindow("Color Cube Sample");

	glutReshapeFunc(onResizeWindow);
	glutDisplayFunc(onRenderScene);
	glutTimerFunc(1000 / 60, onTimer, 0);
	
	setupRc();

	glutMainLoop();

	return EXIT_SUCCESS;
}
