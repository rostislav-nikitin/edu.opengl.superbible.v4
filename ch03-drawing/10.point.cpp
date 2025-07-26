#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <iostream>
#include <cmath>

GLfloat Size = 100.0f;

GLfloat getPointSize(GLfloat minMaxSizes[2])
{
	GLfloat step{};

	glGetFloatv(GL_POINT_SIZE_RANGE, minMaxSizes);
	glGetFloatv(GL_POINT_SIZE_GRANULARITY, &step);

	return step;
}

GLfloat constexpr const GL_PI = 3.1415;

void onRenderScene(void)
{
	
	GLfloat minMaxSizes[2];
	GLfloat pointStep = getPointSize(minMaxSizes);

	std::cout << "Point step: " << pointStep << ", min size: " << minMaxSizes[0] << ", max size: " << minMaxSizes[1] << std::endl;

	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();

	GLfloat xRot = 30.0f;
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);

	GLfloat yRot = 60.0f; // 2.0f * GL_PI;
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);


	glColor3f(0.0f, 1.0f, 0.0f);

	glBegin(GL_LINES);
		glVertex2f(-Size, 0.0f);
		glVertex2f(Size, 0.0f);
		glVertex2f(0.0f, Size);
		glVertex2f(0.0f, -Size);
	glEnd();

	glColor3f(1.0f, 0.0f, 0.0f);

	GLfloat marginLeft = 10.0f;
	int steps = (minMaxSizes[1] - minMaxSizes[0]) / pointStep; 
/*
	glBegin(GL_POINTS);
		for(GLfloat size = minMaxSizes[0], position = -Size + marginLeft; size < 90.0f; size += 1, position += 2.0f)
		{
			glPointSize(size);
			std::cout << "size: " << size << std::endl;
			glVertex2f(position, 10.0f);
		}
	glEnd();
*/

	glBegin(GL_POINTS);

		for(GLfloat angle = 0.0f, y = -36.0f, size = 1.0f;  angle < 6.0 * 2.0 * GL_PI; angle += 0.1f, y += 0.2f, size += 0.5f)
		{
			GLfloat x = 20.0 * cos(angle);
			GLfloat z = 20.0 * sin(angle);

			glPointSize(size);

			glVertex3f(x, y, z);
			
		}


	glEnd();

	//glRectf(-25.0f, 25.0f, 25.0f, -25.0f);
	
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
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	glutCreateWindow("Drawing sample");

	glutReshapeFunc(onResizeWindow);
	glutDisplayFunc(onRenderScene);

	setupRc();

	glutMainLoop();

	return EXIT_SUCCESS;
}
