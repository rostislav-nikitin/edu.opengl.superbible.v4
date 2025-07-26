#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <iostream>

static GLfloat constexpr const Size{100.0f};

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

auto onRenderScene() -> void
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glPushMatrix();
		// Set camera
		glRotatef(22.5f, 1.0f, 0.0f, 0.0f);
		glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
		// Draw objects
		glPushMatrix();
			//glutSolidTorus(10.0f, 20.0f, 36, 36);
			glColor3f(1.0f, 0.0f, 0.0f);
			glutSolidSphere(20.0f, 28, 28);
		glPopMatrix();

	glPopMatrix();
	glutSwapBuffers();
}

auto setupRc() -> void
{
	glClearColor(0.0f, 0.0f, 0.25f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);

	GLfloat ambientLight[] = {0.2f, 0.2f, 0.2f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	glEnable(GL_LIGHTING);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	GLfloat specref[] = {1.0f, 1.0f, 1.0f, 1.0f};
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, 128);

	GLfloat l0a[] = {0.2f, 0.2f, 0.2f, 1.0f};
	glLightfv(GL_LIGHT0, GL_AMBIENT, l0a);
	GLfloat l0d[] = {0.5f, 0.5f, 0.5f, 1.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, l0d);
	GLfloat l0s[] = {1.0f, 1.0f, 1.0f, 1.0f};
	glLightfv(GL_LIGHT0, GL_SPECULAR, l0s);
	GLfloat l0pos[] = {0.0f, 0.0f, 90.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, l0pos);
	GLfloat l0sd[] = {0.0f, 0.0f, -1.0f};
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, l0sd);
	glLighti(GL_LIGHT0, GL_SPOT_CUTOFF, 60.0f);
	

	glEnable(GL_LIGHT0);

	glEnable(GL_NORMALIZE);
}

auto main(int argc, char *argv[]) -> int
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);

	glutCreateWindow("Reflection Sample");

	glutReshapeFunc(onResizeWindow);
	glutDisplayFunc(onRenderScene);

	setupRc();

	glutMainLoop();

	return EXIT_SUCCESS;
}
