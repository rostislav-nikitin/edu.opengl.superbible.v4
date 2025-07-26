#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <math3d/math3d.h>

#include <iostream>
#include <cmath>

static GLfloat constexpr const PI{3.1415f};
static GLfloat constexpr const Size{200.0f};

static GLfloat l0a{PI / 2.0f};

static M3DVector3f constexpr const floorPlane[] = 
{
	{-Size, -Size / 3.0f,  Size},
	{-Size, -Size / 3.0f, -Size},
	{ Size, -Size / 3.0f, -Size},
	{ Size, -Size / 3.0f,  Size}
};

static M3DVector4f planeEquation;

auto onResizeWindow(GLsizei width, GLsizei heigth) -> void
{
	if (heigth == 0)
		heigth = 1;

	glViewport(0, 0, width, heigth);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	GLfloat ratio = GLfloat(width) / GLfloat(heigth);

	GLfloat k = 1.5f;
	if (width < heigth)
		glOrtho(k * (-Size), k * Size, k * (-Size) / ratio, k * Size / ratio, k * (-Size), k * Size);
	else
		glOrtho(k * (-Size) * ratio, k * Size * ratio, k * (-Size), k * Size, k * (-Size), k * Size);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

auto drawFloor() -> void
{
	glColor3f(0.0f, 0.8f, 0.0f);
	glBegin(GL_QUADS);
		glVertex3fv(floorPlane[0]);
		glVertex3fv(floorPlane[3]);
		glVertex3fv(floorPlane[2]);
		glVertex3fv(floorPlane[1]);
	glEnd();
}

auto drawSphere(bool isDrawAsShadow = false) -> void
{
	if (!isDrawAsShadow)
		glColor3f(1.0f, 0.0f, 0.0f);
	else
		glColor3f(0.0f, 0.0f, 0.0f);

	glutSolidSphere(35.0f, 128, 128);
}

auto drawLightSource(bool isDrawAsShadow = false) -> void
{
	if (!isDrawAsShadow)
		glColor3f(1.0f, 1.0f, 0.0f);
	else
		glColor3f(0.0f, 0.0f, 0.0f);
	
	glutSolidSphere(5.0f, 32, 32);
}

auto onRenderScene() -> void
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glPushMatrix();
		// Render light
		GLfloat l0x = Size * 0.9f * cosf(l0a);
		GLfloat l0z = Size * 0.9f * sinf(l0a);


		GLfloat l0p[] = {l0x, 100.0f, l0z, 1.0f};
//		std::cout << l0p[0] << ", " << l0p[1] << ", " << l0p[2] << std::endl;
		glLightfv(GL_LIGHT0, GL_POSITION, l0p);
//		GLfloat l0sd[] = {l0x > 0 ? -1.0f : 1.0f, 0.0f, l0z > 0.0f ? -1.0f : 1.0f, 1.0f};
		GLfloat l0sd[] = {-cosf(l0a), -0.5, -sinf(l0a)};
		glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, l0sd);

		// Render light as object
		glPushMatrix();
			glTranslatef(l0p[0], l0p[1], l0p[2]);
			drawLightSource();
		glPopMatrix();

		glPushMatrix();
			glRotatef(22.5f, 1.0f, 0.0f, 0.0f);
			glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
			// Render coordinates
			// Render floor
			drawFloor();

			glPushMatrix();
				// Draw shadow
				glDisable(GL_DEPTH_TEST);
				glDisable(GL_LIGHTING);
				// Blending

				M3DMatrix44f shadowMatrix;
				m3dMakePlanarShadowMatrix(shadowMatrix, planeEquation, l0p);
				glMultMatrixf(shadowMatrix);

				drawSphere(true);

				glEnable(GL_LIGHTING);
				glEnable(GL_DEPTH_TEST);
			glPopMatrix();

			glPushMatrix();
				// Draw object
				drawSphere();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();

	glutSwapBuffers();
}

auto setupRc() -> void
{
	GLfloat lowLight[] = {0.5f, 0.5f, 0.5f};
//	glClearColor(lowLight[0], lowLight[1], lowLight[2], 1.0f);	
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glFrontFace(GL_CCW);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);
	glEnable(GL_CULL_FACE);

	// Gloabal ambient light
	GLfloat constexpr const ambientLight[] = {0.3f, 0.3f, 0.3f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

	// Color tracking
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Material specular reflection
	GLfloat constexpr const specref[] = {1.0f, 1.0f, 1.0f, 1.0f};
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, 128);

	// Light 0
	GLfloat constexpr const l0a[] = {0.2f, 0.2f, 0.2f, 1.0f};
	glLightfv(GL_LIGHT0, GL_AMBIENT, l0a);
	GLfloat constexpr const l0d[] = {0.4f, 0.4f, 0.4f, 1.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, l0d);
	GLfloat constexpr const l0s[] = {1.0f, 1.0f, 1.0f, 1.0f};
	glLightfv(GL_LIGHT0, GL_SPECULAR, l0s);
	GLfloat constexpr const l0sd[] = {0.0f, 0.0f, -1.0f, 1.0f};
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, l0sd);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 120.0f);
	GLfloat constexpr const l0p[] = {0.0f, 0.0f, Size, 1.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, l0p);
	glEnable(GL_LIGHT0);

	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);

	m3dGetPlaneEquation(planeEquation, floorPlane[1], floorPlane[0], floorPlane[3]);

	// Antialiasing
/*
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
*/
	glEnable(GL_MULTISAMPLE);

	// Fog

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_FOG);
	glFogfv(GL_FOG_COLOR, lowLight);
	glFogf(GL_FOG_START, -200.0f);
	glFogf(GL_FOG_END, 200.0f);
	glFogi(GL_FOG_MODE, GL_LINEAR);

//	glDisable(GL_DITHER);
}

auto onTimer(int) -> void
{
	l0a += PI / 360.0f;
	if(l0a >= 2 * PI)
		l0a = 0.0f;
		
	glutPostRedisplay();
	glutTimerFunc(1000 / 60, onTimer, 0);
}

auto main(int argc, char *argv[]) -> int
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB | GLUT_MULTISAMPLE);

	glutCreateWindow("Mirror Sample");

	glutReshapeFunc(onResizeWindow);
	glutDisplayFunc(onRenderScene);

	setupRc();

	glutTimerFunc(1000 / 60, onTimer, 0);

	glutMainLoop();

	return EXIT_SUCCESS;
}
