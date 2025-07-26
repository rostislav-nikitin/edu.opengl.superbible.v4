#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <cmath>
#include <iostream>

GLfloat constexpr const Size{100.0f};
GLfloat constexpr const GL_PI{3.1415};

GLfloat stencilOffsetX{25.0f};

GLfloat xRot{45.0f};
GLfloat yRot{45.0f};

void onRenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glPushMatrix();

	glRotatef(xRot, 1.0f, 0.0f, 0.0f);

	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	glDisable(GL_STENCIL_TEST);
	glFrontFace(GL_CCW);
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

	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_NEVER, 0x0, 0x0);
	glStencilOp(GL_INCR, GL_INCR, GL_INCR);

	glFrontFace(GL_CW);
	glBegin(GL_TRIANGLE_FAN);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f + stencilOffsetX, 0.0f, 0.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		for(GLfloat angle = 0.0f; angle <= 2.0f * GL_PI + 0.1f; angle += 2.0f * GL_PI / 24.0f)
		{
			GLfloat R = 50.0f * 5.0f / 4.0f;

			GLfloat x = R * cos(angle) + stencilOffsetX;
			GLfloat y = 1.0f;
			GLfloat z = R * sin(angle) + 25.0f;


			glVertex3f(x, y, z);

			//std::cout << angle << ":" << x << ":" << y << ":" << z << std::endl;
				
		}
	glEnd();	

	glStencilFunc(GL_NOTEQUAL, 0x0, 0xff);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

	glFrontFace(GL_CW);
	glBegin(GL_TRIANGLE_FAN);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		bool even{};
		for(GLfloat angle = 0.0f; angle <= 2.0f * GL_PI + 0.1f; angle += 2.0f * GL_PI / 12.0f)
		{
			GLfloat R = 50.0f;

			GLfloat x = R * cos(angle);
			GLfloat y = -90.0f;
			GLfloat z = R * sin(angle);

			if(even = !even)
				glColor3f(1.0f, 0.0f, 0.0f);
			else
				glColor3f(0.0f, 1.0f, 0.0f);

			glVertex3f(x, y, z);

			//std::cout << angle << ":" << x << ":" << y << ":" << z << std::endl;
				
		}
	glEnd();	

	glPopMatrix();

	glutSwapBuffers();
}

void onResizeWindow(GLsizei width, GLsizei height)
{
	
	if(0 >= height)
		height = 1;

	glViewport(0.0f, 0.0f, width, height);

	GLfloat const AspectRatio = GLfloat(width) / GLfloat(height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if(width < height)
		glOrtho(-Size, Size, -Size / AspectRatio, Size / AspectRatio, -Size, Size);
	else
		glOrtho(-Size * AspectRatio, Size * AspectRatio, -Size, Size, -Size, Size);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

GLfloat stencilOffsetXStep = 2.0f;

void onTimer(int)
{
	if(stencilOffsetX > Size)
		stencilOffsetXStep = -stencilOffsetXStep;
	else if(stencilOffsetX <= -Size)
		stencilOffsetXStep = -stencilOffsetXStep;

	stencilOffsetX += stencilOffsetXStep;

	//xRot += 1.0f;
	yRot += 2.0f;

	glutPostRedisplay();
	glutTimerFunc(1000/60, onTimer, 0);
}

void setupRc()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL | GLUT_RGBA);

	glutCreateWindow("Stencil example");

	glutReshapeFunc(onResizeWindow);
	glutDisplayFunc(onRenderScene);
	glutTimerFunc(1000/60, onTimer, 0);
	
	setupRc();
	
	glutMainLoop();

	return EXIT_SUCCESS;
}
