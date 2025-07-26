#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <iostream>

static GLfloat constexpr const Size{100.0f};
static GLfloat constexpr const SideSize{Size / 2.0f};

static GLfloat day{0.0f};

auto onResizeWindow(GLsizei width, GLsizei heigth) -> void
{
	if(heigth == 0)
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
}

auto drawCoordinates() -> void
{
	glBegin(GL_LINES);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-Size, 0.0f, 0.0f);
		glVertex3f( Size, 0.0f, 0.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, -Size, 0.0f);
		glVertex3f(0.0f,  Size, 0.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, -Size);
		glVertex3f(0.0f, 0.0f,  Size);
	glEnd();
}

auto drawCube() -> void
{
	glColor3f(1.0f, 1.0f, 1.0f);


	//Top-Right-Bottom-Left
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, -SideSize);
		glVertex3f(SideSize, 0.0f, 0.0f); 
		glVertex3f(SideSize, 0.0f, -SideSize);
		glVertex3f(SideSize, SideSize, 0.0f);
		glVertex3f(SideSize, SideSize, -SideSize);
		glVertex3f(0.0f, SideSize, 0.0f);
		glVertex3f(0.0f, SideSize, -SideSize);
		glVertex3f(0.0f, 0.0, 0.0f);
		glVertex3f(0.0f, 0.0, -SideSize);
	glEnd();
	//Back
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(0.0f, 0.0f, -SideSize);
		glVertex3f(0.0f, SideSize, -SideSize);
		glVertex3f(SideSize, 0.0f, -SideSize);
		glVertex3f(SideSize, SideSize, -SideSize);
	glEnd();

	//Front
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(SideSize, 0.0f, 0.0f);
		glVertex3f(0.0f, SideSize, 0.0f);
		glVertex3f(SideSize, SideSize, 0.0f);
	glEnd();

}

auto onRenderScene() -> void
{
	glPushMatrix();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glRotatef(11.25f, 1.0f, 0.0f, 0.0f);
		glRotatef(11.25f, 0.0f, 1.0f, 0.0f);
		drawCoordinates();

		glRotatef(day, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.0f, 0.0f, SideSize / 2.0);
		glTranslatef(-SideSize / 2.0, 0.0f, 0.0f);
		glTranslatef(0.0f, -SideSize / 2.0, 0.0f);
		drawCube();
	glPopMatrix();

	glutSwapBuffers();
}

auto onTimer(int) -> void
{
	day += 1.0f;
	if (day >= 360.0f)
		day = 0.0f;

	glutPostRedisplay();
	glutTimerFunc(1000 / 60, onTimer, 0);
}

auto setupRc() -> void
{
	glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_CULL_FACE);
	glShadeModel(GL_FLAT);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);
	glFrontFace(GL_CCW);
}

auto main(int argc, char *argv[]) -> int
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	
	glutCreateWindow("Triangle Stripe Sample");

	glutReshapeFunc(onResizeWindow);
	glutDisplayFunc(onRenderScene);
	glutTimerFunc(1000 / 60, onTimer, 0);

	setupRc();

	glutMainLoop();

	return EXIT_SUCCESS;
}
