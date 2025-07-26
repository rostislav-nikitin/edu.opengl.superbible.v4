#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <iostream>
#include <cmath>

GLfloat Size = 100.0f;

GLfloat getLineWidth(GLfloat minMaxSizes[2])
{
	GLfloat step{};

	glGetFloatv(GL_LINE_WIDTH_RANGE, minMaxSizes);
	glGetFloatv(GL_LINE_WIDTH_GRANULARITY, &step);

	return step;
}

GLfloat constexpr const GL_PI = 3.1415;

void onRenderScene(void)
{
	
	GLfloat minMaxWidths[2];
	GLfloat lineStep = getLineWidth(minMaxWidths);

	std::cout << "Line step: " << lineStep << ", min width: " << minMaxWidths[0] << ", max width: " << minMaxWidths[1] << std::endl;

	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();

	GLfloat xRot = 45.0f;
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);

	GLfloat yRot = 45.0f; // 2.0f * GL_PI;
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

	glBegin(GL_LINES);
		for(GLfloat width = minMaxWidths[0], y = 0.0f, angle = 0.0f, r = 0.5f, g = 0.0f, b = 0.0; width <= minMaxWidths[1]; width += 1.0f, y += 10.0f, angle += (2 * GL_PI / (minMaxWidths[1] - minMaxWidths[0])/ 2.5f), r += 0.05f, g += 0.1f,  b += 0.15f)
		{
			glLineWidth(width);
			glColor3f(r, g, b);

			GLfloat x_0 = 50.0f * cos(angle);
			GLfloat x_1 = 50.0f * cos(angle + GL_PI);
			GLfloat z_0 = 50.0f * sin(angle);
			GLfloat z_1 = 50.0f * sin(angle + GL_PI);

			std::cout << "angle: " << angle << std::endl;
			std::cout << "x_0: " <<  x_0 << "; x_1: " << x_1 << std::endl;
			std::cout << "z_0: " <<  z_0 << "; z_1: " << z_1 << std::endl;

			glVertex3f(x_0, y, z_0);
			glVertex3f(x_1, y, z_1);
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
