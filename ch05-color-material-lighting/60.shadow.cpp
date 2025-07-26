#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math3d/math3d.h>
#include <iostream>

static GLfloat constexpr const Size{200.0f};
static GLfloat day{0.0f};
static M3DVector3f plane[] = 
{
	{-Size, -Size + 3.0f / 4.0f,  Size},
	{ Size, -Size + 3.0f / 4.0f,  Size},
	{-Size, -Size + 3.0f / 4.0f, -Size},
	{ Size, -Size + 3.0f / 4.0f, -Size}
};
static M3DVector4f planeEquation;
static M3DMatrix44f shadowMat;

auto onResizeWindow(GLsizei width, GLsizei heigth) -> void
{
	if (heigth == 0)
		heigth = 1;

	glViewport(0, 0, width, heigth);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	GLfloat ratio = GLfloat(width) / GLfloat(heigth);

	if(width < heigth)
		glOrtho(-Size * 2, Size * 2, -Size * 2 / ratio, Size * 2 / ratio, -Size * 2, Size * 2);
	else
		glOrtho(-Size * 2 * ratio, Size * 2 * ratio, -Size * 2, Size * 2, -Size * 2, Size * 2);

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

void drawCase()
{
	M3DVector3f normal;

	glFrontFace(GL_CCW);
	// Top Plane
	glBegin(GL_TRIANGLE_STRIP);
		M3DVector3f top[] = 
		{
			{-97.5f, 17.5f, 32.5f},
			{97.5f, 17.5f, 32.5f},
			{-97.5, 17.5f, -32.5f},
			{97.5f, 17.5f, -32.5f}
		};
		m3dFindNormal(normal, top[0], top[1], top[2]);
//		m3dNormalizeVector(normal);
		glNormal3fv(normal);
		glVertex3fv(top[0]);
		glVertex3fv(top[1]);
		glVertex3fv(top[2]);
		glVertex3fv(top[3]);
	glEnd();

	// Bottom Plane
	glBegin(GL_TRIANGLE_STRIP);
		M3DVector3f bottom[] = 
		{
			{-97.5f, -17.5f, 32.5f},
			{-97.5f, -17.5f, -32.5f},
			{97.5f, -17.5f, 32.5f},
			{97.5f, -17.5f, -32.5f}
		};
		m3dFindNormal(normal, bottom[0], bottom[1], bottom[2]);
//		m3dNormalizeVector(normal);
//		std::cout << normal[0] << ", " << normal[1] << ", " << normal[2] << std::endl;
		glNormal3fv(normal);
		glVertex3fv(bottom[0]);
		glVertex3fv(bottom[1]);
		glVertex3fv(bottom[2]);
		glVertex3fv(bottom[3]);
	glEnd();

	// Front Plane
	glBegin(GL_TRIANGLE_STRIP);
		M3DVector3f front[] = 
		{
			{-97.5f, -17.5f, 32.5f},
			{-97.5f, 17.5f, 32.5f},
			{-97.5f, -17.5f, -32.5f},
			{-97.5f, 17.5f, -32.5f}
		};
		m3dFindNormal(normal, front[0], front[1], front[2]);
//		m3dNormalizeVector(normal);
//		std::cout << normal[0] << ", " << normal[1] << ", " << normal[2] << std::endl;
		glNormal3fv(normal);
		glVertex3fv(front[0]);
		glVertex3fv(front[1]);
		glVertex3fv(front[2]);
		glVertex3fv(front[3]);

	glEnd();

	// Back Plane
	glBegin(GL_TRIANGLE_STRIP);
		M3DVector3f back[] = 
		{
			{97.5f, -17.5f, 32.5f},
			{97.5f, -17.5f, -32.5f},
			{97.5f, 17.5f, 32.5f},
			{97.5f, 17.5f, -32.5f}
		};
		m3dFindNormal(normal, back[0], back[1], back[2]);
//		m3dNormalizeVector(normal);
//		std::cout << normal[0] << ", " << normal[1] << ", " << normal[2] << std::endl;
		glVertex3fv(back[0]);
		glVertex3fv(back[1]);
		glVertex3fv(back[2]);
		glVertex3fv(back[3]);
	glEnd();

	// Left Plane
	glBegin(GL_TRIANGLE_STRIP);
		M3DVector3f left[] = 
		{	
			{-97.5f, 17.5f, -32.5f},
			{97.5f, 17.5f, -32.5f},
			{-97.5f, -17.5f, -32.5f},
			{97.5f, -17.5f, -32.5f}
		};
		m3dFindNormal(normal, left[0], left[1], left[2]);
//		m3dNormalizeVector(normal);
//		std::cout << normal[0] << ", " << normal[1] << ", " << normal[2] << std::endl;
		glVertex3fv(left[0]);
		glVertex3fv(left[1]);
		glVertex3fv(left[2]);
		glVertex3fv(left[3]);
	glEnd();

	// Right Plane
	glBegin(GL_TRIANGLE_STRIP);
		M3DVector3f right[] = 
		{
			{97.5f, -17.5f, 32.5f},
			{97.5f, 17.5f, 32.5f},
			{-97.5, -17.5f, 32.5f},
			{-97.5f, 17.5f, 32.5f}
		};
		m3dFindNormal(normal, right[0], right[1], right[2]);
//		m3dNormalizeVector(normal);
//		std::cout << normal[0] << ", " << normal[1] << ", " << normal[2] << std::endl;
		glVertex3fv(right[0]);
		glVertex3fv(right[1]);
		glVertex3fv(right[2]);
		glVertex3fv(right[3]);
	glEnd();
}

void drawLeg()
{
	M3DVector3f normal;
	// Plane connected to the case
	glFrontFace(GL_CCW);
	glBegin(GL_TRIANGLE_STRIP);
		M3DVector3f cse[] = 
		{
			{-5.0f, 25.0f, -10.0f},
			{5.0f, 25.0f, -10.0f},
			{-5.0f, 24.0f, 10.0f},
			{5.0f, 24.0f, 10.0f}
		};
		m3dFindNormal(normal, cse[0], cse[1], cse[2]);
		glNormal3fv(normal);
		glVertex3fv(cse[0]);
		glVertex3fv(cse[1]);
		glVertex3fv(cse[2]);
		glVertex3fv(cse[3]);
	glEnd();
	// -- Top 
	glFrontFace(GL_CCW);
	glBegin(GL_TRIANGLE_STRIP);
		M3DVector3f ddtop[] = 
		{
			{-5.0f, 25.0f, 10.0f},
			{5.0f, 25.0f, 10.0f},
			{-5.0f, 25.0f, -10.0f},
			{5.0f, 25.0f, -10.0f}
		};
		m3dFindNormal(normal, ddtop[0], ddtop[1], ddtop[2]);
		glNormal3fv(normal);
		glVertex3fv(ddtop[0]);
		glVertex3fv(ddtop[1]);
		glVertex3fv(ddtop[2]);
		glVertex3fv(ddtop[3]);
	glEnd();
	// - Top
	glFrontFace(GL_CW);
	glBegin(GL_TRIANGLE_STRIP);
		M3DVector3f dtop[] = 
		{
			{-5.0f, 24.0f, 9.0f},
			{5.0f, 24.0f, 9.0f},
			{-5.0f, 24.0f, -10.0f},
			{5.0f, 24.0f, -10.0f}
		};
		m3dFindNormal(normal, dtop[0], dtop[2], dtop[1]);
//		m3dNormalizeVector(normal);
//		std::cout << normal[0] << ", " << normal[1] << ", " << normal[2] << std::endl;
		glNormal3fv(normal);
		glVertex3fv(dtop[0]);
		glVertex3fv(dtop[1]);
		glVertex3fv(dtop[2]);
		glVertex3fv(dtop[3]);
	glEnd();
	// ||+ Right
	glFrontFace(GL_CCW);
	glBegin(GL_TRIANGLE_STRIP);
		M3DVector3f vvpright[] =
		{
			{-5.0f, 10.0f, 10.0f},
			{ 5.0f, 10.0f, 10.0f},
			{-5.0f, 25.0f, 10.0f},
			{ 5.0f, 25.0f, 10.0f}
		};
		m3dFindNormal(normal, vvpright[0], vvpright[1], vvpright[2]);
		glNormal3fv(normal);
		glVertex3fv(vvpright[0]);
		glVertex3fv(vvpright[1]);
		glVertex3fv(vvpright[2]);
		glVertex3fv(vvpright[3]);
	glEnd();
	// |+ Left
	glFrontFace(GL_CW);
	glBegin(GL_TRIANGLE_STRIP);
		M3DVector3f vpleft[] = 
		{
			{-5.0f, 10.0f, 9.0f},
			{ 5.0f, 10.0f, 9.0f},
			{-5.0f, 24.0f, 9.0f},
			{ 5.0f, 24.0f, 9.0f}
		};
		m3dFindNormal(normal, vpleft[0], vpleft[2], vpleft[1]);
		glNormal3fv(normal);
		glVertex3fv(vpleft[0]);
		glVertex3fv(vpleft[1]);
		glVertex3fv(vpleft[2]);
		glVertex3fv(vpleft[3]);
	glEnd();
	// || Right
	glFrontFace(GL_CCW);
	glBegin(GL_TRIANGLE_STRIP);
		M3DVector3f vvright[] = 
		{
			{-2.5f, -25.0f, 10.0f},
			{ 2.5f, -25.0f, 10.0f},
			{-2.5f,  10.0f, 10.0f},
			{ 2.5f,  10.0f, 10.0f}
		};
		m3dFindNormal(normal, vvright[0], vvright[1], vvright[2]);
		glNormal3fv(normal);
		glVertex3fv(vvright[0]);
		glVertex3fv(vvright[1]);
		glVertex3fv(vvright[2]);
		glVertex3fv(vvright[3]);
	glEnd();
	// | Left
	glFrontFace(GL_CW);
	glBegin(GL_TRIANGLE_STRIP);
		M3DVector3f vleft[] = 
		{
			{-2.5f, -25.0f, 9.0f},
			{ 2.5f, -25.0f, 9.0f},
			{-2.5f,  10.0f, 9.0f},
			{ 2.5f,  10.0f, 9.0f}
		};
		m3dFindNormal(normal, vleft[0], vleft[2], vleft[1]);
		glNormal3fv(normal);
		glVertex3fv(vleft[0]);
		glVertex3fv(vleft[1]);
		glVertex3fv(vleft[2]);
		glVertex3fv(vleft[3]);
	glEnd();
	// _ Bottom
	glFrontFace(GL_CW);
	glBegin(GL_TRIANGLE_STRIP);
		M3DVector3f ubottom[]
		{
			{-2.5f, -25.0f, 10.0f},
			{ 2.5f,  -25.0f, 10.0f},
			{-2.5f, -25.0f, 9.0f},
			{ 2.5f,  -25.0f, 9.0f}
		};
		m3dFindNormal(normal, ubottom[0], ubottom[2], ubottom[1]);
		glNormal3fv(normal);
		glVertex3fv(ubottom[0]);
		glVertex3fv(ubottom[1]);
		glVertex3fv(ubottom[2]);
		glVertex3fv(ubottom[3]);
	glEnd();
	// -- Front
	glFrontFace(GL_CCW);
	glBegin(GL_TRIANGLE_STRIP);
		M3DVector3f ddfront[] =
		{
			{-5.0f, 24.0f, 10.0f},
			{-5.0f, 25.0f, 10.0f},
			{-5.0f, 24.0f,  9.0f},
			{-5.0f, 25.0f,  9.0f}
		};
		m3dFindNormal(normal, ddfront[0], ddfront[1], ddfront[2]);
		glNormal3fv(normal);
		glVertex3fv(ddfront[0]);
		glVertex3fv(ddfront[1]);
		glVertex3fv(ddfront[2]);
		glVertex3fv(ddfront[3]);
	glEnd();
	// -- Back
	glFrontFace(GL_CW);
	glBegin(GL_TRIANGLE_STRIP);
		M3DVector3f ddback[] = 
		{
			{5.0f, 24.0f, 10.0f},
			{5.0f, 25.0f, 10.0f},
			{5.0f, 24.0f, 9.0f},
			{5.0f, 25.0f, 9.0f}
		};
		m3dFindNormal(normal, ddback[0], ddback[2], ddback[1]);
		glNormal3fv(normal);
		glVertex2fv(ddback[0]);
		glVertex2fv(ddback[1]);
		glVertex2fv(ddback[2]);
		glVertex2fv(ddback[3]);
	glEnd();
	// |+ Front
	glFrontFace(GL_CCW);
	glBegin(GL_TRIANGLE_STRIP);
		M3DVector3f vpfront[] = 
		{
			{-5.0f, 10.0f, 10.0f},
			{-5.0f, 24.0f, 10.0f},
			{-5.0f, 10.0f,  9.0f},
			{-5.0f, 24.0f,  9.0f}
		};
		m3dFindNormal(normal, vpfront[0], vpfront[1], vpfront[2]);
		glNormal3fv(normal);
		glVertex3fv(vpfront[0]);
		glVertex3fv(vpfront[1]);
		glVertex3fv(vpfront[2]);
		glVertex3fv(vpfront[3]);
	glEnd();
	// |+ Back
	glFrontFace(GL_CW);
	glBegin(GL_TRIANGLE_STRIP);
		M3DVector3f vpback[] = 
		{
			{5.0f, 10.0f, 10.0f},
			{5.0f, 24.0f, 10.0f},
			{5.0f, 10.0f,  9.0f},
			{5.0f, 24.0f,  9.0f}
		};
		m3dFindNormal(normal, vpback[0], vpback[2], vpback[1]);
		glNormal3fv(normal);
		glVertex3fv(vpback[0]);
		glVertex3fv(vpback[1]);
		glVertex3fv(vpback[2]);
		glVertex3fv(vpback[3]);
	glEnd();
	// --- Front 
	glFrontFace(GL_CCW);
	glBegin(GL_TRIANGLE_STRIP);
		M3DVector3f dddfront[] = 
		{
			{-2.5f, 10.0f, 10.0f},
			{-5.0f, 10.0f, 10.0f},
			{-2.5f, 10.0f,  9.0f},
			{-5.0f, 10.0f,  9.0f}
		};
		m3dFindNormal(normal, dddfront[0], dddfront[1], dddfront[2]);
		glNormal3fv(normal);
		glVertex3fv(dddfront[0]);
		glVertex3fv(dddfront[1]);
		glVertex3fv(dddfront[2]);
		glVertex3fv(dddfront[3]);
	glEnd();
	// --- Back
	glFrontFace(GL_CCW);
	glBegin(GL_TRIANGLE_STRIP);
		M3DVector3f dddback[] =
		{
			{ 5.0f, 10.0f, 10.0f},
			{-2.5f, 10.0f, 10.0f},
			{ 5.0f, 10.0f,  9.0f},
			{-2.5f, 10.0f,  9.0f}
		};
		m3dFindNormal(normal, dddback[0], dddback[1], dddback[2]);
		glNormal3fv(normal);
		glVertex3fv(dddback[0]);
		glVertex3fv(dddback[1]);
		glVertex3fv(dddback[2]);
		glVertex3fv(dddback[3]);
	glEnd();
	// | Front
	glFrontFace(GL_CCW);
	glBegin(GL_TRIANGLE_STRIP);
		M3DVector3f vfront[] =
		{
			{-2.5f, -25.0f, 10.0f},
			{-2.5f,  10.0f, 10.0f},
			{-2.5f, -25.0f,  9.0f},
			{-2.5f,  10.0f,  9.0f}
		};
		m3dFindNormal(normal, vfront[0], vfront[1], vfront[2]);
		glNormal3fv(normal);
		glVertex3fv(vfront[0]);
		glVertex3fv(vfront[1]);
		glVertex3fv(vfront[2]);
		glVertex3fv(vfront[3]);
	glEnd();
	// | Back
	glFrontFace(GL_CW);
	glBegin(GL_TRIANGLE_STRIP);
		M3DVector3f vback[] =
		{
			{2.5f, -25.0f, 10.0f},
			{2.5f,  10.0f, 10.0f},
			{2.5f, -25.0f,  9.0f},
			{2.5f,  10.0f,  9.0f}
		};
		m3dFindNormal(normal, vback[0], vback[2], vback[1]);
		glNormal3fv(normal);
		glVertex3fv(vback[0]);
		glVertex3fv(vback[1]);
		glVertex3fv(vback[2]);
		glVertex3fv(vback[3]);
	glEnd();
}

void drawChip(bool drawAsShadow = false)
{
	if (drawAsShadow)
		glColor3f(0.0f, 0.0f, 0.0f);
	
	if (!drawAsShadow)
		glColor3f(0.25f, 0.25f, 0.25f);

	drawCase();

	if (!drawAsShadow)
		glColor3f(1.0f, 1.0f, 1.0f);

	for(int sideIdx = 0; sideIdx < 2; ++sideIdx)
	{
		glPushMatrix();
		glRotatef(180.0f * sideIdx, 0.0f, 1.0f, 0.0f);
		for(int legIdx = 0; legIdx < 8; ++legIdx)
		{
			glPushMatrix();
			glTranslatef(-67.5f + legIdx * 20.0f, -24.5f, 42.5f);
			drawLeg();
			glPopMatrix();
		}
		glPopMatrix();
	}
}

auto drawPlane() -> void
{
	glColor3f(0.25f, 0.0f, 0.0f);
	glFrontFace(GL_CCW);
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3fv(plane[0]);
		glVertex3fv(plane[1]);
		glVertex3fv(plane[2]);
		glVertex3fv(plane[3]);
	glEnd();
}

auto onRenderScene() -> void
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
		glEnable(GL_LIGHTING);
		// Draw code
		// Set camera
		glRotatef(22.5f, 1.0f, 0.0f, 0.0f);
		glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
		// Draw coordinates
		glPushAttrib(GL_LIGHTING_BIT);
			glDisable(GL_LIGHTING);
			drawPlane();
		glPopAttrib();
		glPushMatrix();
			// Draw objects
			glRotatef(0 - day, 0.0f, 1.0f, 0.0f);
			drawChip();
			// Draw shadows
			glDisable(GL_DEPTH_TEST);
			glDisable(GL_LIGHTING);
				glMultMatrixf(shadowMat);
				drawChip(true);
			glEnable(GL_DEPTH_TEST);
		glPopMatrix();
		// Draw coordinates
		glPushAttrib(GL_LIGHTING_BIT);
			glDisable(GL_LIGHTING);
			drawCoordinates();
		glPopAttrib();
	glPopMatrix();
	glutSwapBuffers();
}

auto setupRc() -> void
{
	glClearColor(0.0f, 0.0f, 0.25f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glFrontFace(GL_CCW);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);
	glEnable(GL_CULL_FACE);

	GLfloat ambientLight[] = {0.3f, 0.3f, 0.3f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	glEnable(GL_LIGHTING);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	GLfloat specref[] = {1.0f, 1.0f, 1.0f, 1.0f};
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, 128);

	GLfloat l0a[] = {0.3f, 0.3f, 0.3f, 1.0f};
	glLightfv(GL_LIGHT0, GL_AMBIENT, l0a);
	GLfloat l0d[] = {0.3f, 0.3f, 0.3f, 1.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, l0d);
	GLfloat l0s[] = {1.0f, 1.0f, 1.0f, 1.0f};
	glLightfv(GL_LIGHT0, GL_SPECULAR, l0s);
	GLfloat l0spotDir[] = {0.0f, 0.0f, -1.0f};
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, l0spotDir);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 180.0f);
	GLfloat l0p[] = {0.0f, Size, Size / 2.0f, 1.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, l0p);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);


	m3dGetPlaneEquation(planeEquation, plane[0], plane[1], plane[2]);
	m3dMakePlanarShadowMatrix(shadowMat, planeEquation, l0p);
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

	glutCreateWindow("Shadow Sample");

	glutReshapeFunc(onResizeWindow);
	glutDisplayFunc(onRenderScene);
	
	setupRc();

	glutTimerFunc(1000 / 60, onTimer, 0);

	glutMainLoop();

	return EXIT_SUCCESS;
}
