#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <iostream>
#include <cmath>

GLfloat Size = 100.0f;

GLfloat constexpr const GL_PI = 3.1415;

GLfloat xRot = -30.0f;
GLfloat yRot = 60.0f;

void onTimer(int)
{
	xRot += 1.0f;
	if(xRot > 360.0f)
		xRot = 0.0f;

	yRot += 1.0f;
	if(yRot > 360.0f)
		yRot = 0.0f;
	glutPostRedisplay();
	glutTimerFunc(1000/60, onTimer, 0);
}

void onRenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

	//GLfloat xRot = -30.0f;
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);

	//GLfloat yRot = 60.0f; // 2.0f * GL_PI;
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);


	glColor3f(0.0f, 1.0f, 0.0f);

	glBegin(GL_LINES);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-Size, 0.0f, 0.0f);
		glVertex3f(Size, 0.0f, 0.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, Size, 0.0f);
		glVertex3f(0.0f, -Size, 0.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, Size);
		glVertex3f(0.0f, 0.0f, -Size);
	glEnd();


	glColor3f(1.0f, 0.0f, 0.0f);

	GLfloat marginLeft = 10.0f;

	glFrontFace(GL_CW);
	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(0.0f, 90.0f, 0.0f);
		bool even{true};

		for(GLfloat angle = 0.0; angle <= 2 * GL_PI + 0.1f; angle += 2 *GL_PI / 12.0f)
		{
		
			GLfloat x = 50.0f * cos(angle);
			GLfloat z = 50.0f * sin(angle);

			if(even)
				glColor3f(1.0f, 0.0f, 0.0f);
			else
				glColor3f(0.0f, 1.0f, 0.0f);

			glVertex3f(x, 0.0f, z);

			even = !even;
		}
	glEnd();

		glFrontFace(GL_CCW);
		glBegin(GL_TRIANGLE_FAN);
		glVertex3f(0.0f, 0.0f, 0.0f);

		for(GLfloat angle = 0.0; angle <= 2 * GL_PI + 0.1f; angle += 2 * GL_PI / 12.0f)
		{	
			GLfloat x = 50.0f * cos(angle);
			GLfloat z = 50.0f * sin(angle);

			if(even)
				glColor3f(1.0f, 0.0f, 0.0f);
			else
				glColor3f(0.0f, 1.0f, 0.0f);

			glVertex3f(x, 0.0f, z);

			even = !even;
		}
	glEnd();

	glPopMatrix();

	glutSwapBuffers();
}

void onResizeWindow(GLsizei width, GLsizei height)
{
	if(height == 0)
		height = 1;

	glViewport(0, 0, width, height);

	GLfloat ratio = GLfloat(width) / GLfloat(height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if(width <= height)
		glOrtho(-Size, Size, -Size / ratio, Size / ratio, -Size, Size);
	else
		glOrtho(-Size * ratio, Size * ratio, -Size, Size, -Size, Size);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void setupRc(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glShadeModel(GL_FLAT);
	glFrontFace(GL_CW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutCreateWindow("Drawing sample");

	glutReshapeFunc(onResizeWindow);
	glutDisplayFunc(onRenderScene);
	glutTimerFunc(1000/60, onTimer, 0);

	setupRc();

	glutMainLoop();

	return EXIT_SUCCESS;
}
