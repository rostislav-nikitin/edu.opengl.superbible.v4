#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <iostream>

GLfloat constexpr const Size{400.0f};

static GLfloat xRot{45.0f};
GLfloat constexpr const xRotStep{1.0f};

static GLfloat yRot{30.0f};
GLfloat constexpr const yRotStep{0.0f};

void onResizeWindow(GLsizei width, GLsizei heigth)
{
	if(0 == heigth)
		heigth = 1;

	glViewport(0, 0, width, heigth);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	GLfloat ratio = GLfloat(width) / GLfloat(heigth);
/*
	if(width < heigth)
		glOrtho(-Size, Size, -Size / ratio, Size / ratio, -Size, Size);
	else
		glOrtho(-Size * ratio, Size * ratio, -Size, Size, -Size, Size);
*/

	gluPerspective(45.0f, ratio, 1.0f, 2 * Size);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutSwapBuffers();
}
void drawCoordinates()
{
	// Drow coordinate guidlines
	glBegin(GL_LINES);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-Size, 0.0f, 0.0f);
		glVertex3f(Size, 0.0f, 0.0f);

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, -Size, 0.0f);
		glVertex3f(0.0f, Size, 0.0f);

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, -Size);
		glVertex3f(0.0f, 0.0f, Size);
	glEnd();
}

void drawCase()
{
	glFrontFace(GL_CCW);
	// Top Plane
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(-97.5f, 17.5f, 32.5f);
		glVertex3f(97.5f, 17.5f, 32.5f);
		glVertex3f(-97.5, 17.5f, -32.5f);
		glVertex3f(97.5f, 17.5f, -32.5f);
	glEnd();

	// Bottom Plane
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(-97.5f, -17.5f, 32.5f);
		glVertex3f(-97.5f, -17.5f, -32.5f);
		glVertex3f(97.5f, -17.5f, 32.5f);
		glVertex3f(97.5f, -17.5f, -32.5f);
	glEnd();

	// Front Plane
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(-97.5f, -17.5f, 32.5f);
		glVertex3f(-97.5, 17.5f, 32.5f);
		glVertex3f(-97.5f, -17.5f, -32.5f);
		glVertex3f(-97.5f, 17.5f, -32.5f);
	glEnd();

	// Back Plane
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(97.5f, -17.5f, 32.5f);
		glVertex3f(97.5f, -17.5f, -32.5f);
		glVertex3f(97.5f, 17.5f, 32.5f);
		glVertex3f(97.5f, 17.5f, -32.5f);
	glEnd();

	// Left Plane
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(-97.5f, 17.5f, -32.5f);
		glVertex3f(97.5f, 17.5f, -32.5f);
		glVertex3f(-97.5f, -17.5f, -32.5f);
		glVertex3f(97.5f, -17.5f, -32.5f);
	glEnd();

	// Right Plane
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(97.5f, -17.5f, 32.5f);
		glVertex3f(97.5f, 17.5f, 32.5f);
		glVertex3f(-97.5, -17.5f, 32.5f);
		glVertex3f(-97.5f, 17.5f, 32.5f);
	glEnd();
}

void drawLeg()
{
	// Plane connected to the case
	glFrontFace(GL_CCW);
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(-5.0f, 25.0f, -10.0f);
		glVertex3f(5.0f, 25.0f, -10.0f);
		glVertex3f(-5.0f, 24.0f, 10.0f);
		glVertex3f(5.0f, 24.0f, 10.0f);
	glEnd();
	// -- Top 
	glFrontFace(GL_CCW);
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(-5.0f, 25.0f, 10.0f);
		glVertex3f(5.0f, 25.0f, 10.0f);
		glVertex3f(-5.0f, 25.0f, -10.0f);
		glVertex3f(5.0f, 25.0f, -10.0f);
	glEnd();
	// - Top
	glFrontFace(GL_CW);
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(-5.0f, 24.0f, 9.0f);
		glVertex3f(5.0f, 24.0f, 9.0f);
		glVertex3f(-5.0f, 24.0f, -10.0f);
		glVertex3f(5.0f, 24.0f, -10.0f);
	glEnd();
	// ||+ Right
	glFrontFace(GL_CCW);
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(-5.0f, 10.0f, 10.0f);
		glVertex3f(5.0f,  10.0f, 10.0f);
		glVertex3f(-5.0f, 25.0f, 10.0f);
		glVertex3f(5.0f,  25.0f, 10.0f);
	glEnd();
	// |+ Left
	glFrontFace(GL_CW);
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(-5.0f, 10.0f, 9.0f);
		glVertex3f(5.0f,  10.0f, 9.0f);
		glVertex3f(-5.0f, 24.0f, 9.0f);
		glVertex3f(5.0f,  24.0f, 9.0f);
	glEnd();
	// || Right
	glFrontFace(GL_CCW);
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(-2.5f, -25.0f, 10.0f);
		glVertex3f(2.5f,  -25.0f, 10.0f);
		glVertex3f(-2.5f,  10.0f, 10.0f);
		glVertex3f(2.5f,   10.0f, 10.0f);
	glEnd();
	// | Left
	glFrontFace(GL_CW);
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(-2.5f, -25.0f, 9.0f);
		glVertex3f(2.5f,  -25.0f, 9.0f);
		glVertex3f(-2.5f,  10.0f, 9.0f);
		glVertex3f(2.5f,   10.0f, 9.0f);
	glEnd();
	// _ Bottom
	glFrontFace(GL_CW);
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(-2.5f, -25.0f, 10.0f);
		glVertex3f(2.5f,  -25.0f, 10.0f);
		glVertex3f(-2.5f, -25.0f, 9.0f);
		glVertex3f(2.5f,  -25.0f, 9.0f);
	glEnd();
	// -- Front
	glFrontFace(GL_CCW);
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(-5.0f, 24.0f, 10.0f);
		glVertex3f(-5.0f, 25.0f, 10.0f);
		glVertex3f(-5.0f, 24.0f, 9.0f);
		glVertex3f(-5.0f, 25.0f, 9.0f);
	glEnd();
	// -- Back
	glFrontFace(GL_CW);
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(5.0f, 24.0f, 10.0f);
		glVertex3f(5.0f, 25.0f, 10.0f);
		glVertex3f(5.0f, 24.0f, 9.0f);
		glVertex3f(5.0f, 25.0f, 9.0f);
	glEnd();
	// |+ Front
	glFrontFace(GL_CCW);
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(-5.0f, 10.0f, 10.0f);
		glVertex3f(-5.0f, 24.0f, 10.0f);
		glVertex3f(-5.0f, 10.0f, 9.0f);
		glVertex3f(-5.0f, 24.0f, 9.0f);
	glEnd();
	// |+ Back
	glFrontFace(GL_CW);
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(5.0f, 10.0f, 10.0f);
		glVertex3f(5.0f, 24.0f, 10.0f);
		glVertex3f(5.0f, 10.0f, 9.0f);
		glVertex3f(5.0f, 24.0f, 9.0f);
	glEnd();
	// -- Front 
	glFrontFace(GL_CCW);
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(-2.5f, 10.0f, 10.0f);
		glVertex3f(-5.0f, 10.0f, 10.0f);
		glVertex3f(-2.5f, 10.0f, 9.0f);
		glVertex3f(-5.0f, 10.0f, 9.0f);
	glEnd();
	// -- Back
	glFrontFace(GL_CCW);
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(5.0f, 10.0f, 10.0f);
		glVertex3f(-2.5f, 10.0f, 10.0f);
		glVertex3f(5.0f, 10.0f, 9.0f);
		glVertex3f(-2.5f, 10.0f, 9.0f);
	glEnd();
	// | Front
	glFrontFace(GL_CCW);
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(-2.5f, -25.0f, 10.0f);
		glVertex3f(-2.5f,  10.0f, 10.0f);
		glVertex3f(-2.5f, -25.0f, 9.0f);
		glVertex3f(-2.5f,  10.0f, 9.0f);
	glEnd();
	// | Back
	glFrontFace(GL_CW);
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(2.5f, -25.0f, 10.0f);
		glVertex3f(2.5f,  10.0f, 10.0f);
		glVertex3f(2.5f, -25.0f, 9.0f);
		glVertex3f(2.5f,  10.0f, 9.0f);
	glEnd();
}


void drawChip()
{
	glColor3f(0.25f, 0.25f, 0.25f);
	drawCase();

	glColor3f(1.0f, 1.0f, 1.0f);
	for(int sideIdx = 0; sideIdx < 2; ++sideIdx)
	{
		glPushMatrix();
		glRotatef(180.0f * sideIdx, 0.0f, 1.0f, 0.0f);
		for(int legIdx = 0; legIdx < 8; ++legIdx)
		{
			glPushMatrix();
			glTranslatef(-67.5f + legIdx * 20.0f, -24.5f, 42.5f);
			drawLeg();
			glPopMatrix();
		}
		glPopMatrix();
	}
}

void onRenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	glPushMatrix();
		glTranslatef(0.0f, 0.0f, -425.0f);
		glRotatef(22.5f, 1.0f, 0.0f, 0.0f);
		glRotatef(45.5f, 0.0f, 1.0f, 0.0f);
		drawCoordinates();

		glRotatef(1 * xRot, 0.0f, 1.0f, 0.0f);
		glRotatef(2 * xRot, 1.0f, 0.0f, 0.0f);
		drawChip();
	glPopMatrix();

	glutSwapBuffers();
}

void onTimer(int)
{
	xRot += xRotStep;
	if(xRot >= 360.0f)
		xRot = 0.0f;

	yRot += yRotStep;
	if(yRot >= 360.0f)
		yRot = 0.0f;

	glutPostRedisplay();

	glutTimerFunc(1000 / 60, onTimer, 0);
}
void setupRc(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glShadeModel(GL_FLAT);
	glFrontFace(GL_CCW);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH  | GLUT_RGB);
	glutCreateWindow("Chip Model");
	glutReshapeFunc(onResizeWindow);
	glutDisplayFunc(onRenderScene);
	glutTimerFunc(1000/60, onTimer, 0);
	
	setupRc();

	glutMainLoop();

	return EXIT_SUCCESS;
}
