#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <iostream>

GLfloat constexpr const Size{200.0f};

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

	if(width < heigth)
		glOrtho(-Size, Size, -Size / ratio, Size / ratio, -Size, Size);
	else
		glOrtho(-Size * ratio, Size * ratio, -Size, Size, -Size, Size);

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
		glVertex3f(0.0f, 35.0f, 65.0f);
		glVertex3f(195.0f, 35.0f, 65.0f);
		glVertex3f(0.0f, 35.0f, 0.0f);
		glVertex3f(195.0f, 35.0f, 0.0f);
	glEnd();

	// Bottom Plane
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(0.0f, 0.0f, 65.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(195.0f, 0.0f, 65.0f);
		glVertex3f(195.0f, 0.0f, 0.0f);
	glEnd();

	// Front Plane
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(0.0f, 0.0f, 65.0f);
		glVertex3f(0.0f, 35.0f, 65.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 35.0f, 0.0f);
	glEnd();

	// Back Plane
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(195.0f, 0.0f, 65.0f);
		glVertex3f(195.0f, 0.0f, 0.0f);
		glVertex3f(195.0f, 35.0f, 65.0f);
		glVertex3f(195.0f, 35.0f, 0.0f);
	glEnd();

	// Left Plane
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(0.0f, 35.0f, 0.0f);
		glVertex3f(195.0f, 35.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(195.0f, 0.0f, 0.0f);
	glEnd();

	// Right Plane
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(195.0f, 0.0f, 65.0f);
		glVertex3f(195.0f, 35.0f, 65.0f);
		glVertex3f(0.0f, 0.0f, 65.0f);
		glVertex3f(0.0f, 35.0f, 65.0f);
	glEnd();
}

void drawLeg()
{
	// Plane connected to the case
	glFrontFace(GL_CCW);
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(10.0f, 17.5f, 65.0f);
		glVertex3f(20.0f, 17.5f, 65.0f);
		glVertex3f(10.0f, 16.5f, 65.0f);
		glVertex3f(20.0f, 16.5f, 65.0f);
	glEnd();
	// -- Top 
	glFrontFace(GL_CCW);
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(10.0f, 17.5f, 75.0f);
		glVertex3f(20.0f, 17.5f, 75.0f);
		glVertex3f(10.0f, 17.5f, 65.0f);
		glVertex3f(20.0f, 17.5f, 65.0f);
	glEnd();
	// - Top
	glFrontFace(GL_CW);
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(10.0f, 16.5f, 74.0f);
		glVertex3f(20.0f, 16.5f, 74.0f);
		glVertex3f(10.0f, 16.5f, 65.0f);
		glVertex3f(20.0f, 16.5f, 65.0f);
	glEnd();
	// ||+ Right
	glFrontFace(GL_CCW);
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(10.0f, -2.5f, 75.0f);
		glVertex3f(20.0f, -2.5f, 75.0f);
		glVertex3f(10.0f, 17.5, 75.0f);
		glVertex3f(20.0f, 17.5, 75.0f);
	glEnd();
	// |+ Left
	glFrontFace(GL_CW);
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(10.0f, -2.5f, 74.0f);
		glVertex3f(20.0f, -2.5f, 74.0f);
		glVertex3f(10.0f, 16.5, 74.0f);
		glVertex3f(20.0f, 16.5, 74.0f);
	glEnd();
	// || Right
	glFrontFace(GL_CCW);
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(12.5f, -32.5f, 75.0f);
		glVertex3f(17.5f, -32.5f, 75.0f);
		glVertex3f(12.5f, -2.5f, 75.0f);
		glVertex3f(17.5f, -2.5f, 75.0f);
	glEnd();
	// | Left
	glFrontFace(GL_CW);
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(12.5f, -32.5f, 74.0f);
		glVertex3f(17.5f, -32.5f, 74.0f);
		glVertex3f(12.5f, -2.5f, 74.0f);
		glVertex3f(17.5f, -2.5f, 74.0f);
	glEnd();
	// _ Bottom
	glFrontFace(GL_CW);
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(12.5f, -32.5f, 75.0f);
		glVertex3f(17.5f, -32.5f, 75.0f);
		glVertex3f(12.5f, -32.5f, 74.0f);
		glVertex3f(17.5f, -32.5f, 74.0f);
	glEnd();
	// -- Front
	glFrontFace(GL_CCW);
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(10.0f, 16.5f, 75.0f);
		glVertex3f(10.0f, 17.5f, 75.0f);
		glVertex3f(10.0f, 16.5f, 65.0f);
		glVertex3f(10.0f, 17.5f, 65.0f);
	glEnd();
	// -- Back
	glFrontFace(GL_CW);
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(20.0f, 16.5f, 75.0f);
		glVertex3f(20.0f, 17.5f, 75.0f);
		glVertex3f(20.0f, 16.5f, 65.0f);
		glVertex3f(20.0f, 17.5f, 65.0f);
	glEnd();
	// |+ Front
	glFrontFace(GL_CCW);
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(10.0f, -2.5f, 75.0f);
		glVertex3f(10.0f, 16.5f, 75.0f);
		glVertex3f(10.0f, -2.5f, 74.0f);
		glVertex3f(10.0f, 16.5f, 74.0f);
	glEnd();
	// |+ Back
	glFrontFace(GL_CW);
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(20.0f, -2.5f, 75.0f);
		glVertex3f(20.0f, 16.5f, 75.0f);
		glVertex3f(20.0f, -2.5f, 74.0f);
		glVertex3f(20.0f, 16.5f, 74.0f);
	glEnd();
	// -- Front 
	glFrontFace(GL_CCW);
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(12.5f, -2.5f, 75.0f);
		glVertex3f(10.0f, -2.5f, 75.0f);
		glVertex3f(12.5f, -2.5f, 74.0f);
		glVertex3f(10.0f, -2.5f, 74.0f);
	glEnd();
	// -- Back
	glFrontFace(GL_CCW);
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(20.0f, -2.5f, 75.0f);
		glVertex3f(12.5f, -2.5f, 75.0f);
		glVertex3f(20.0f, -2.5f, 74.0f);
		glVertex3f(12.5f, -2.5f, 74.0f);
	glEnd();
	// | Front
	glFrontFace(GL_CCW);
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(12.5f, -32.5f, 75.0f);
		glVertex3f(12.5f, -2.5f, 75.0f);
		glVertex3f(12.5f, -32.5f, 74.0f);
		glVertex3f(12.5f, -2.5f, 74.0f);
	glEnd();
	// | Back
	glFrontFace(GL_CW);
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(17.5f, -32.5f, 75.0f);
		glVertex3f(17.5f, -2.5f, 75.0f);
		glVertex3f(17.5f, -32.5f, 74.0f);
		glVertex3f(17.5f, -2.5f, 74.0f);
	glEnd();
}

void onRenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	drawCoordinates();
	glColor3f(0.25f, 0.25f, 0.25f);
	drawCase();
	glColor3f(1.0f, 1.0f, 1.0f);
	//glPushMatrix();
	//glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	drawLeg();
	//glPopMatrix();

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
