#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <math3d/math3d.h>

#include "glFrame.h"

#include <iostream>
#include <vector>
#include <random>

static GLfloat constexpr const Size{100.0f};
static size_t constexpr const NumSpheres{50};

static std::vector<GLFrame> spheres{NumSpheres};
static GLFrame camera;

static std::random_device rdev;
static std::default_random_engine reng(rdev());
static std::uniform_int_distribution<int> uniform_distr(-Size, Size);


auto getRandomValue() -> GLfloat
{
	return uniform_distr(reng);
}

auto onWindowResize(GLsizei width, GLsizei heigth) -> void
{
	if(heigth == 0)
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

	gluPerspective(45.0f, ratio, 1.0, 4 * Size);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

auto drawCoordinateAxis() -> void
{
	glBegin(GL_LINES);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-Size, 0.0f, 0.0f);
		glVertex3f( Size, 0.0f, 0.0f);
	glEnd();
	glBegin(GL_LINES);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f,  Size, 0.0f);
		glVertex3f(0.0f, -Size, 0.0f);
	glEnd();
	glBegin(GL_LINES);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, -Size);
		glVertex3f(0.0f, 0.0f,  Size);
	glEnd();
}

auto drawGround() -> void
{
	GLfloat constexpr const Step{10.0f};
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
		for(GLfloat x = -Size, z = -Size; x <= Size; x += Step, z += Step)
		{
			glVertex3f(x, 0.0f, -Size);
			glVertex3f(x, 0.0f,  Size);
			glVertex3f(-Size, 0.0f, z);
			glVertex3f( Size, 0.0f, z);
		}
	glEnd();
}

auto onRenderScene() -> void
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

		camera.ApplyCameraTransform();

		drawCoordinateAxis();
		drawGround();

		glColor3f(1.0f, 0.0f, 1.0f);
		for(auto &sphere : spheres)
		{
			glPushMatrix();
				sphere.ApplyActorTransform();
				glutSolidSphere(5.0f, 13, 26);
			glPopMatrix();
		}

		glColor3f(1.0f, 1.0f, 0.0f);
		glutSolidTorus(5.0f, 15.0f, 16, 16);

	glPopMatrix();

	glutSwapBuffers();
}

auto setupRc() -> void
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	glShadeModel(GL_FLAT);
	glPolygonMode(GL_FRONT, GL_LINE);
	glPolygonMode(GL_BACK, GL_LINE);
	glFrontFace(GL_CCW);
}

auto initCamera() -> void
{
	//camera.RotateLocalX(m3dDegToRad(-10.0f)); 
	//camera.RotateWorld(m3dDegToRad(-22.5f), 1.0f, 0.0f, 0.0f); 
	//camera.TranslateWorld(0.0f, 0.0f, 50.0f);
//	camera.TranslateWorld(0.0f, -25.0f, 0.0f);
//	camera.RotateWorld(m3dDegToRad(-22.5f), 1.0f, 0.0f, 0.0f); 
//	camera.RotateWorld(m3dDegToRad(-11.25f), 0.0f, 1.0f, 0.0f); 
//	camera.RotateLocalX(m3dDegToRad(-25.0f));
	camera.MoveUp(10.0f);
//	camera.MoveForward(-120.0f);
}

auto initSpheres() -> void
{
	for(auto &sphere : spheres)
	{
		sphere.SetOrigin(getRandomValue(), 0.0f, getRandomValue());	
	}
}

auto onTimer(int) -> void
{
	
//	camera.RotateLocalY(m3dDegToRad(-1.0f)); 
	camera.RotateWorld(m3dDegToRad(-1.0f), 0.0f, 1.0f, 0.0f); 
	glutPostRedisplay();
//	glutTimerFunc(1000 / 60, onTimer, 0);
}

auto onSpecialKey(int key, int x, int y)
{
	if(key == GLUT_KEY_UP)
		camera.MoveForward(1.0f);
	if(key == GLUT_KEY_DOWN)
		camera.MoveForward(-1.0f);
	if(key == GLUT_KEY_LEFT)
		camera.RotateLocalY(m3dDegToRad(1.0f));
//		camera.RotateWorld(m3dDegToRad(1.0f), 0.0f, 1.0f, 0.0f);
	if(key == GLUT_KEY_RIGHT)
		camera.RotateLocalY(m3dDegToRad(-1.0f));
//		camera.RotateWorld(-m3dDegToRad(1.0f), 0.0f, 1.0f, 0.0f);
	// Refresh the Window
	glutPostRedisplay();
}

auto main(int argc, char *argv[]) -> int
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);

	glutCreateWindow("Classes Sample");

	glutReshapeFunc(onWindowResize);
	glutDisplayFunc(onRenderScene);
	glutSpecialFunc(onSpecialKey);
	glutTimerFunc(1000 / 60, onTimer, 0);

	setupRc();

	initCamera();
	initSpheres();

	glutMainLoop();

	return EXIT_SUCCESS;
}
