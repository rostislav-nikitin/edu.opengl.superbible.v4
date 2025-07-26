#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <math3d.h>

#include <iostream>

static GLfloat constexpr const Size{100.0f};

static GLfloat rotY{0.0f};

auto onResizeWindow(GLsizei width, GLsizei heigth) -> void
{
	if(0 == heigth)
		heigth  = 1;

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

auto drawAxis() -> void
{
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
		glVertex3f(-Size, 0.0f, 0.0f);
		glVertex3f( Size, 0.0f, 0.0f);
	glEnd();

	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
		glVertex3f(0.0f, -Size, 0.0f);
		glVertex3f(0.0f,  Size, 0.0f);
	glEnd();

	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
		glVertex3f(0.0f, 0.0f, -Size);
		glVertex3f(0.0f, 0.0f,  Size);
	glEnd();
}

auto onRenderScene() -> void
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// One Way
	/*
	// Position axis
	M3DMatrix44f rotationMatrixX;
	M3DMatrix44f rotationMatrixY;
	M3DMatrix44f rotationMatrix;
	M3DMatrix44f translationMatrix;
	M3DMatrix44f transformationMatrix;

	//m3dLoadIdentity44(transformationMatrix);
	m3dTranslationMatrix44(translationMatrix, 25.0f, 0.0f, 0.0f);
	m3dRotationMatrix44(rotationMatrixY, m3dDegToRad(rotY), 0.0f, 1.0f, 0.0f);
	m3dRotationMatrix44(rotationMatrixX, m3dDegToRad(22.5f), 1.0f, 0.0f, 0.0f);
	m3dMatrixMultiply44(rotationMatrix, rotationMatrixX, rotationMatrixY);
	m3dMatrixMultiply44(transformationMatrix, translationMatrix, rotationMatrix);

	glLoadMatrixf(transformationMatrix);
	*/

	// Another Way
	
	M3DMatrix44f rotationMatrixX;
	M3DMatrix44f rotationMatrixY;
	M3DMatrix44f translationMatrix;

	m3dTranslationMatrix44(translationMatrix, 25.0f, 0.0f, 0.0f);
	m3dRotationMatrix44(rotationMatrixX, m3dDegToRad(22.5f), 1.0f, 0.0f, 0.0f);
	m3dRotationMatrix44(rotationMatrixY, m3dDegToRad(rotY), 0.0f, 1.0f, 0.0f);

	glLoadIdentity();
	glMultMatrixf(translationMatrix);
	glMultMatrixf(rotationMatrixX);	
	glMultMatrixf(rotationMatrixY);	
	

	drawAxis();

	glColor3f(0.0f, 1.0f, 0.0f);
	glutSolidTorus(5.0f, 15.0f, 16, 16);

	glutSwapBuffers();
}

auto onTimer(int) -> void
{
	rotY += 1.0f;

	if(rotY >= 360.0f)
		rotY = 0.0f;

	glutPostRedisplay();

	glutTimerFunc(1000 / 60, onTimer, 0);
}

auto setupRc(void) -> void
{
	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT, GL_LINE);
	glPolygonMode(GL_BACK, GL_LINE);
	glEnable(GL_CULL_FACE);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

auto main(int argc, char *argv[]) -> int
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);

	glutCreateWindow("Matrix Sample");
	glutReshapeFunc(onResizeWindow);
	glutDisplayFunc(onRenderScene);
	glutTimerFunc(1000 / 60, onTimer, 0);

	setupRc();

	glutMainLoop();

	return EXIT_SUCCESS;
}
