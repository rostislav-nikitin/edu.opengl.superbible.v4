#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <math3d.h>

#include <iostream>
#include <vector>

static GLfloat constexpr const Size{100.0f};

static GLfloat rotY{0.0f};

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
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
		glVertex3f(-Size, 0.0f, 0.0f);
		glVertex3f( Size, 0.0f, 0.0f);
	glEnd();
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
		glVertex3f(0.0f, -Size, 0.0f);
		glVertex3f(0.0f,  Size, 0.0f);
	glEnd();
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
		glVertex3f(0.0f, 0.0f, -Size);
		glVertex3f(0.0f, 0.0f,  Size);
	glEnd();
}

typedef GLfloat vertex[3];

auto rotateVertex(GLfloat angleDeg, std::vector<GLfloat> inputVertex) -> std::vector<GLfloat>
{
	std::vector<GLfloat> outputVertex(3);
	M3DMatrix44f rotationMatrix;
	m3dRotationMatrix44(rotationMatrix, m3dDegToRad(angleDeg), 0.0f, 1.0f, 0.0f);
	m3dTransformVector3(outputVertex.data(), inputVertex.data(), rotationMatrix);

	return outputVertex;
}

auto drawCube(GLsizei side) -> void
{

	glColor3f(1.0f, 0.0f, 0.0f);
	glFrontFace(GL_CW);
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3fv(rotateVertex(rotY, {-side / 2.0f, -side / 2.0f,  side / 2.0f}).data());
		glVertex3fv(rotateVertex(rotY, { side / 2.0f, -side / 2.0f,  side / 2.0f}).data());
		glVertex3fv(rotateVertex(rotY, {-side / 2.0f, -side / 2.0f, -side / 2.0f}).data());
		glVertex3fv(rotateVertex(rotY, { side / 2.0f, -side / 2.0f, -side / 2.0f}).data());
	glEnd();
	glFrontFace(GL_CCW);
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3fv(rotateVertex(rotY, {-side / 2.0f, side / 2.0f,  side / 2.0f}).data());
		glVertex3fv(rotateVertex(rotY, { side / 2.0f, side / 2.0f,  side / 2.0f}).data());
		glVertex3fv(rotateVertex(rotY, {-side / 2.0f, side / 2.0f, -side / 2.0f}).data());
		glVertex3fv(rotateVertex(rotY, { side / 2.0f, side / 2.0f, -side / 2.0f}).data());
	glEnd();
}

auto onSceneRender() -> void
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set camera
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -25.0f);
	glRotatef(11.25f, 1.0f, 0.0f, 0.0f);
	glRotatef(22.5f, 0.0f, 1.0f, 0.0f);

	drawCoordinates();

	drawCube(20.0f);
	
	glutSwapBuffers();
}

auto onTimer(int) -> void
{
	rotY += 1.0f;
	if(rotY >= 360.0f)
		rotY = 0.0f;

	glutPostRedisplay();
	glutTimerFunc(1000 / 60, onTimer, 0);
}

auto setupRc() -> void
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glShadeModel(GL_FLAT);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);
	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_CULL_FACE);
//	glPloygonMode(GL_FRONT_
}

auto main(int argc, char *argv[]) -> int
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);

	glutCreateWindow("Vertex Transformation Sample");
	glutReshapeFunc(onWindowResize);
	glutDisplayFunc(onSceneRender);
	glutTimerFunc(1000 / 60, onTimer, 0);

	setupRc();

	glutMainLoop();

	return EXIT_SUCCESS;
}
