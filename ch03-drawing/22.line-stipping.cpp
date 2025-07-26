#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <iostream>

GLfloat constexpr const Size{100.0f};

void onResizeWindow(GLsizei width, GLsizei heigth)
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

void onRenderScene(void)
{
	GLint constexpr const FactorsCount = 4;
	GLfloat constexpr const YOffset = 25.0f;
	GLushort constexpr const Stipples[] = { 0xFFFF, 0xAAAA, 0x9248, 0x8888 };
	GLfloat constexpr const Step = (2 * Size - 2.0 * YOffset) / GLfloat((FactorsCount * sizeof(Stipples) - 1) / sizeof(GLushort));

	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_LINES);

		glColor3f(1.0f, 0.0f, 0.0f);

		GLfloat y = -Size + YOffset;

		for(GLint factor = 1; factor <= FactorsCount; ++factor)
		{
			for(int idx = 0; idx < sizeof(Stipples) / sizeof(GLushort); ++idx)
			{
				std::cout << factor << ":" << idx << ":" << y << std::endl;
				GLushort stipple = Stipples[idx];

				glLineStipple(factor, stipple);
				glVertex2f(-Size, y);
				glVertex2f(Size, y);

				y += Step;
			}
		}

	glEnd();

	glutSwapBuffers();
}

void setupRc(void)
{
	glClearColor(0.0f, 0.0f, 0.75f, 1.0f);
	glEnable(GL_LINE_STIPPLE);
}


int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	glutCreateWindow("Line Stripping Sample");
	glutReshapeFunc(onResizeWindow);
	glutDisplayFunc(onRenderScene);

	setupRc();

	glutMainLoop();

	return EXIT_SUCCESS;
}
