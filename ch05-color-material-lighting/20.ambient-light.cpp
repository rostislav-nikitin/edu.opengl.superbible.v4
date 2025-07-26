#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <iostream>

GLfloat constexpr const Size{100.0f};

auto onWindowResize(GLsizei width, GLsizei heigth) -> void
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
		glVertex3f(Size, 0.0f, 0.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, -Size, 0.0f);
		glVertex3f(0.0f, Size, 0.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0, -Size);
		glVertex3f(0.0f, 0.0f, Size);
	glEnd();
}

auto onRenderScene() -> void
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glPushMatrix();

	// Drawing code
	glRotatef(22.5f, 1.0f, 0.0f, 0.0f);
	glRotatef(22.5f, 0.0f, 1.0f, 0.0f);

	drawCoordinates();

//		GLfloat gray[] = {1.0f, 0.0f, 0.0f};
//		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);

		glColor3f(1.0f, 0.25f, 0.25f);
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
		glutSolidTorus(10.0f, 30.0f, 32, 32);

	glPopMatrix();

	glutSwapBuffers();
}

auto setupRc() -> void
{
	glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glEnable(GL_COLOR_MATERIAL);

	GLfloat ambientLight[] = {0.5f, 0.5f, 0.5f, 1.0f};
	glEnable(GL_LIGHTING);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
}

auto main(int argc, char *argv[]) -> int
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);

	glutCreateWindow("Ambient Light Sample");

	glutReshapeFunc(onWindowResize);
	glutDisplayFunc(onRenderScene);

	setupRc();

	glutMainLoop();

	return EXIT_SUCCESS;
}
