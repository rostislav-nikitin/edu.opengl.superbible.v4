#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <iostream>
#include <cmath>

GLfloat constexpr const Size{100.0};
GLfloat constexpr const PI{3.1415};

static GLfloat camXAngle{11.25f};
static GLfloat camYAngle{22.5f};
static GLfloat alpha{};

auto radToDeg(GLfloat rad) -> GLfloat
{
	return rad * 360.0f / (2.0f * PI);
}


void onResizeWindow(GLsizei width, GLsizei heigth)
{
	if(0 == heigth)
		heigth = 1;

	glViewport(0, 0, width, heigth);

	GLfloat ratio = GLfloat(width) / GLfloat(heigth);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if(width < heigth)
		glOrtho(-Size, Size, -Size / ratio, Size / ratio, -Size, Size);
	else
		glOrtho(-Size * ratio, Size * ratio, -Size, Size, -Size, Size);

//	gluPerspective(45.0f, ratio, 1.0, 2 * Size);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void drawCoordinates(void)
{
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

void onRenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
//	glTranslatef(0.0f, 0.0f, -100.0f);
//	glRotatef(35.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(camXAngle, 1.0f, 0.0f, 0.0f);
	glRotatef(camYAngle, 0.0f, 1.0f, 0.0f);

	drawCoordinates();


	glColor3f(1.0f, 0.0f, 0.0f);
	for(GLfloat angle = 0.0f; angle < 2.0f * PI; angle += PI / 2.0f)
	{
		glPushMatrix();
		GLfloat x = 25.0f * cos(angle + alpha);
		GLfloat z = -25.0f * sin(angle + alpha);
		glTranslatef(x, 0.0f, z);
		glutSolidSphere(5.0f, 16, 16);
		glPopMatrix();
	}
	glColor3f(0.0f, 1.0f, 0.0f);
	for(GLfloat angle = 0.0f; angle < 2.0f * PI; angle += PI / 2.0f)
	{
		glPushMatrix();
		GLfloat z = -35.0f * cos(angle + alpha / 2.0f);
		GLfloat y =  35.0f * sin(angle + alpha / 2.0f);
		glTranslatef(0.0, y, z);
		glutSolidSphere(3.0f, 16, 16);
		glPopMatrix();
	}

	glutSwapBuffers();
}

void onTimer(int)
{
	alpha += 0.05f;
	if(alpha >= 360.0f)
		alpha = 0.0f;

	camYAngle += 1.0f;
	if(360.0f <= camYAngle)
		camYAngle = 0.0f;

	glutPostRedisplay();

	glutTimerFunc(1000/60, onTimer, 0);
}

void onSpecialKey(int key, int x, int y)
{
	if(GLUT_KEY_DOWN == key)
	{
		if(camXAngle < 180.0f)
			camXAngle += 1.0f;
	}
	else if(GLUT_KEY_UP == key)
	{
		if(camXAngle > 0.0f)
			camXAngle -= 1.0f;
	}
	
}

void setupRc()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
}

auto main(int argc, char *argv[]) -> int
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	
	glutCreateWindow("Sphere Sample");

	glutReshapeFunc(onResizeWindow);
	glutDisplayFunc(onRenderScene);
	glutSpecialFunc(onSpecialKey);
	glutTimerFunc(1000/60, onTimer, 0);

	setupRc();

	glutMainLoop();

	return EXIT_SUCCESS;
}
