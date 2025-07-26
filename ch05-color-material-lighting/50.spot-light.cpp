#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <iostream>

static GLfloat constexpr const Size{100.0f};

static GLfloat day{0.0f};

auto onResizeWindow(GLsizei width, GLsizei heigth) -> void
{
	if (heigth == 0)
		heigth = 1;

	glViewport(0, 0, width, heigth);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	GLfloat ratio = GLfloat(width) / GLfloat(heigth);

	if (width < heigth)
		glOrtho(-Size, Size, -Size / ratio, Size / ratio, -Size, Size);
	else
		glOrtho(-Size * ratio, Size * ratio, -Size, Size, -Size, Size);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

auto drawCoordinates() -> void
{
	glDisable(GL_LIGHTING);
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
	glEnable(GL_LIGHTING);
}

auto onRenderScene() -> void
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	// Set coordinates
	glPushMatrix();
		glRotatef(22.5f, 1.0f, 0.0f, 0.0f);
		glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
		
		drawCoordinates();

		glPushMatrix();
			// Transform object coorinates
			glRotatef(0.0f - day, 0.0f, 1.0f, 0.0f);
			glColor3f(1.0f, 0.0f, 0.0f);
			glutSolidTorus(10.0f, 20.0f, 96, 192);
		glPopMatrix();
	glPopMatrix();

	glutSwapBuffers();
}

auto setupRc() -> void
{
	glClearColor(0.0f, 0.0f, 0.25f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
	glShadeModel(GL_SMOOTH);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);
	glEnable(GL_CULL_FACE);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	GLfloat specref[] = {1.0f, 1.0f, 1.0f, 1.0f};
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, 128);

	GLfloat ambientLight[] = {0.3f, 0.3f, 0.3f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	glEnable(GL_LIGHTING);

	GLfloat l0ambient[] = {0.3, 0.3f, 0.3f, 1.0f};
	GLfloat l0diffuse[] = {0.5f, 0.5, 0.5f, 0.5f};
	GLfloat l0specular[] = {1.0f, 1.0f, 1.0f};
	glLightfv(GL_LIGHT0, GL_AMBIENT, l0ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, l0diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, l0specular);
	GLfloat l0pos[] = {0.0f, 100.0f, 100.0f, 1.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, l0pos);
	GLfloat sporDir[] = {0.0f, 0.0f, -1.0f};
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 50.0f);
	glEnable(GL_LIGHT0);

	glEnable(GL_NORMALIZE);	
}

auto onTimer(int) -> void
{

	day += 1.0f;
	if (day >= 360.0f)
		day = 0.0f;

	glutPostRedisplay();	
	glutTimerFunc(1000 / 60, onTimer, 0);
}

auto main(int argc, char *argv[]) -> int
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);

	glutCreateWindow("Spot Light Sample");

	glutReshapeFunc(onResizeWindow);
	glutDisplayFunc(onRenderScene);

	setupRc();

	glutTimerFunc(1000 / 60, onTimer, 0);

	glutMainLoop();

	return EXIT_SUCCESS;
}
