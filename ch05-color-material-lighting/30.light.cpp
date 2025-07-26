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
		glVertex3f(Size, 0.0f, 0.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, -Size, 0.0f);
		glVertex3f(0.0f, Size, 0.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, -Size);
		glVertex3f(0.0f, 0.0f, Size);
	glEnd();
}

auto onRenderScene() -> void
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
		// Move camera
		glRotatef(22.5f, 1.0f, 0.0f, 0.0f);
		glRotatef(45.0f - day, 0.0f, 1.0f, 0.0f);
		drawCoordinates();

		// Render objects
		glPushMatrix();
			glColor3f(0.25f, 0.25f, 0.25f);
			glTranslatef(-50.0f, 0.0f, 0.0f);
			glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
			glutSolidTorus(10.f, 25.0f, 36, 36);
		glPopMatrix();

		glPushMatrix();
			glColor3f(0.5f, 0.5f, 0.5f);
			glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
			glutSolidTorus(10.f, 25.0f, 36, 36);
		glPopMatrix();

		glPushMatrix();
			glColor3f(1.0f, 1.0f, 1.0f);
			glTranslatef(50.0f, 0.0f, 0.0f);
			glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
			glutSolidTorus(10.f, 25.0f, 36, 36);
		glPopMatrix();

	glPopMatrix();

	glutSwapBuffers();
}

auto setupRc() -> void
{
	glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glShadeModel(GL_SHADER);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);

	glEnable(GL_LIGHTING);
	// Background lighting
	GLfloat ambientLight[] = {0.5f, 0.5f, 0.5f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

	// Objects lighting based on object color
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Light0
	GLfloat light0AmbientLight[] = {0.3f, 0.3f, 0.3f, 1.0f};
	GLfloat light0DiffuseLight[] = {0.7f, 0.7f, 0.7f, 1.0f};
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0AmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0DiffuseLight);
	glEnable(GL_LIGHT0);

	GLfloat light0Position[] = {-50.f, 75.0f, 0.0f, 1.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, light0Position);

	glEnable(GL_NORMALIZE); 

}


auto onTimer(int) -> void
{
	day += 1.0f;
	if(day >= 360.0f)
		day = 0.0f;

	glutPostRedisplay();
	glutTimerFunc(1000 / 60, onTimer, 0);
}

auto main(int argc, char *argv[]) -> int
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);

	glutCreateWindow("Light Sample");

	glutReshapeFunc(onResizeWindow);
	glutDisplayFunc(onRenderScene);

	setupRc();

	glutTimerFunc(1000 / 60, onTimer, 0);

	glutMainLoop();

	return EXIT_SUCCESS;
}
