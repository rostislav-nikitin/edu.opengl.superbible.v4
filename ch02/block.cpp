#include <cstdlib>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <iostream>

GLfloat 
	rx = -25.0f, 
	ry = 25.0f, 
	rw = 50.0f, 
	rh = 50.0f, 
	rdx = 1.0f,
	rdy = 2.0f,
	sx = -100.0f,
	sy = -100.0f,
	sw = 200.0f,
	sh = 200.0f;

void onRenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0f, 1.0f, 0.0f);
	glRectf(rx, ry, rx + rw, ry - rh);

	glutSwapBuffers();
}

void onWindowResize(GLsizei w, GLsizei h)
{
	GLfloat ratio;
	if(h == 0)
		h = 1;

	glViewport(0, 0, w, h);

	ratio = GLfloat(w) / GLfloat(h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if(w <= h)
		glOrtho(-100.0f, 100.0f, -100.0f / ratio, 100.0f / ratio, -1.0, 1.0);
	else
		glOrtho(-100.0f * ratio, 100.0f * ratio, -100.0f, 100.0f, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void onTimer(int value)
{
	//std::cout << "Timer test" << std::endl;	
	
	if(rx + rw >= sx + sw || rx <= sx)
		rdx = -rdx;

	rx += rdx;

	if(ry - rh <= sy || ry >= sy + sh)
		rdy = -rdy;

	ry += rdy;

	glutPostRedisplay();
	glutTimerFunc(1000/60, onTimer, 0);
}

void setupRc()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow("Sample");
	glutReshapeFunc(onWindowResize);
	glutDisplayFunc(onRenderScene);
	glutTimerFunc(1000/60, onTimer, 0);
	setupRc();
	glutMainLoop();

	return EXIT_SUCCESS;
}
