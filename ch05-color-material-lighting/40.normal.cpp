#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <math3d/math3d.h>

#include <iostream>

static GLfloat constexpr const Size{200.0f};

static GLfloat l0x{-50.0f};
static GLfloat l0z{0.0f};
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
		// Light
		//glPopMatrix();

		// Set coordinates
		glRotatef(22.5f, 1.0f, 0.0f, 0.0f);
		glRotatef(45.0f, 0.0f, 1.0f, 0.0f);


		glPushMatrix();
			GLfloat l0Position[] = { l0x, 90.0f, l0z, 1.0f };
			glLightfv(GL_LIGHT0, GL_POSITION, l0Position);
			glDisable(GL_LIGHTING);
			glColor3f(1.0f, 1.0f, 0.0f);
			glTranslatef(l0Position[0], l0Position[1], l0Position[2]);
			glutSolidSphere(5.0f, 32, 32);
			glEnable(GL_LIGHTING);
		glPopMatrix();

		glDisable(GL_LIGHTING);
		drawCoordinates();
		glEnable(GL_LIGHTING);

		glPushMatrix();
			glRotatef(day, 0.0f, 1.0f, 0.0f);

			glTranslatef(-37.5f, 0.0f, 0.0f);
			glTranslatef(0.0f, 0.0f, 37.5f);
			M3DVector3f normal;
		
			// Top Square
			glBegin(GL_TRIANGLE_STRIP);
				glColor3f(1.0f, 0.0f, 0.0f);
				normal[0] = 0.0f; normal[1] = 9.0f; normal[2] = 0.0f;
//				m3dNormalizeVector(normal);
				glNormal3f(normal[0], normal[1], normal[2]);
				glVertex3f( 0.0f, 0.0f,   0.0f);
				glVertex3f(75.0f, 0.0f,   0.0f);
				glVertex3f( 0.0f, 0.0f, -75.0f);
				glVertex3f(75.0f, 0.0f, -75.0f);
			glEnd();
			// Left Square
			glBegin(GL_TRIANGLE_STRIP);
				glColor3f(1.0f, 0.0f, 0.0f);
				M3DVector3f s2[] = 
				{
					{-75.0f, -75.0f, 0.0f},
					{0.0f, 0.0f, 0.0f},
					{-75.0f, -75.0f, -75.0f},
					{0.0f, 0.0f, -75.0f}
				};

				m3dFindNormal(normal, s2[0], s2[1], s2[2]);
//				m3dNormalizeVector(normal);
				glNormal3fv(normal);

				glVertex3fv(s2[0]);
				glVertex3fv(s2[1]);
				glVertex3fv(s2[2]);
				glVertex3fv(s2[3]);
			glEnd();

			// Right
			glBegin(GL_TRIANGLE_STRIP);
				glColor3f(1.0f, 0.0f, 0.0f);
				M3DVector3f s3[] = 
				{
					{75.0f, 0.0f, 0.0f},
					{150.0f, -75.0f, 0.0f},
					{75.0f, 0.0f, -75.0f},
					{150.0f,  -75.0f, -75.0f}
				};
				m3dFindNormal(normal, s3[0], s3[1], s3[2]);
				glNormal3fv(normal);
				glVertex3fv(s3[0]);
				glVertex3fv(s3[1]);
				glVertex3fv(s3[2]);
				glVertex3fv(s3[3]);
			glEnd();
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
	//glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);

	// Lighting
	glEnable(GL_LIGHTING);

	// Gloabal Ambient
	GLfloat ambientLight[] = {0.3f, 0.3f, 0.3f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

	// Color tracking
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// LIGHT0 config
	GLfloat l0AmbientLight[] = {0.3f, 0.3f, 0.3f, 1.0f};
	GLfloat l0DiffuseLight[] = {0.7f, 0.7f, 0.7f, 1.0f};
	glLightfv(GL_LIGHT0, GL_AMBIENT, l0AmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, l0DiffuseLight);
	glEnable(GL_LIGHT0);

//	GLfloat 
	glEnable(GL_NORMALIZE);
}

auto onSpecial(int key, int x, int y) -> void
{
	switch(key)
	{
		case GLUT_KEY_RIGHT:
			if(l0x < Size)
				l0x += 5.0;
			break;
		case GLUT_KEY_LEFT:
			if(l0x > -Size)
				l0x -= 5.0;
			break;
		case GLUT_KEY_DOWN:
			if(l0z < Size)
				l0z += 5.0;
			break;
		case GLUT_KEY_UP:
			if(l0z > -Size)
				l0z -= 5.0;
			break;
	}

	glutPostRedisplay();
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

	glutCreateWindow("Normal Sample");

	glutReshapeFunc(onResizeWindow);
	glutDisplayFunc(onRenderScene);
	glutSpecialFunc(onSpecial);
	
	setupRc();

	glutTimerFunc(1000 / 60, onTimer, 0);

	glutMainLoop();

	return EXIT_SUCCESS;
}
