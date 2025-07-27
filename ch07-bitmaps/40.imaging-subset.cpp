//#include <EGL/egl.h>
//#include <GL/glx.h>

//#include <GL/glew.h>
#include <glad/glad.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/gli.hpp>

#include <cstdlib>

#include <iostream>

static GLfloat constexpr const Size{100.f};

static GLfloat lumMat[16] =
{
	0.30f, 0.30f, 0.30f, 0.0f,
	0.59f, 0.59f, 0.59f, 0.0f,
	0.11f, 0.11f, 0.11f, 0.0f,
	0.00f, 0.00f, 0.00f, 1.00f
};

static GLfloat sharpenMat[3][3] = 
{
	 0.0f, -1.0f,  0.0f,
	-1.0f,  5.0f, -1.0f,
	 0.0f, -1.0f,  0.0f
};

static GLfloat embrossMat[3][3] = 
{
	 2.0f,  0.0f,  0.0f,
	 0.0f, -1.0f,  0.0f,
	 0.0f,  0.0f, -1.0f
};

static GLint histogram[256];
static GlImage::GlImage image {GlImage::make_tga_image("./sample_640x426.tga")};

auto setupRc() -> void
{
	glClearColor(0.0f, 0.0f, 0.25f, 1.0f);

	//std::cout << "Ext: " << gltIsExtSupported("GL_ARB_imaging") << std::endl;
}

auto onResizeWindow(GLsizei width, GLsizei heigth) -> void
{
	if (heigth == 0)
		heigth = 1;

	glViewport(0, 0, width, heigth);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	GLfloat ratio = GLfloat(width) / GLfloat(heigth);

	if (width < heigth)
		glOrtho(0, Size, 0, Size / ratio, 0, Size);
	else
		glOrtho(0, Size * ratio, 0, Size, 0, Size);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

auto onRenderScene() -> void
{
	GLint i{};
	GLint viewport[4];
	GLint largest{};
	static GLubyte invertTable[256][3];
	static GLint histogram[256];

	glClear(GL_COLOR_BUFFER_BIT);

	glGetIntegerv(GL_VIEWPORT, viewport);
	glPixelZoom(GLfloat(viewport[2]) / GLfloat(image.getWidth()), GLfloat(viewport[3]) / GLfloat(image.getHeigth()));

	glRasterPos2i(0, 0);


	//std::cout << &glConvolutionFilter2D << std::endl;

	//glConvolutionFilter2D(GL_CONVOLUTION_2D, GL_RGB, 3, 3, GL_LUMINANCE, GL_FLOAT, sharpenMat);
	//glEnable(GL_CONVOLUTION_2D);

 //void * glConvolutionFilter2D=(void *)ARB_get_proc_address("glConvolutionFilter2D");

/*

	glConvolutionFilter2D(GL_CONVOLUTION_2D, GL_RGB, 3, 3, GL_LUMINANCE, GL_FLOAT, embrossMat);
	glEnable(GL_CONVOLUTION_2D);
	glMatrixMode(GL_COLOR);
	glLoadMatrixf(lumMat);
	glMatrixMode(GL_MODELVIEW);
*/

/*
	for(int idx = 0; idx < 256; ++idx)
	{
		invertTable[idx][0] = GLubyte(255 - idx);
		invertTable[idx][1] = GLubyte(255 - idx);
		invertTable[idx][2] = GLubyte(255 - idx);
	}
	
	glColorTable(GL_COLOR_TABLE, GL_RGB, 256, GL_RGB, GL_UNSIGNED_BYTE, invertTable);
	glEnable(GL_COLOR_TABLE);
*/
/*
	glMatrixMode(GL_COLOR);
	glScalef(1.25f, 1.25f, 1.25f);
	glMatrixMode(GL_MODELVIEW);
*/
	glDrawPixels(image.getWidth(), image.getHeigth(), image.getFormat(), GL_UNSIGNED_BYTE, image.getContent());


	glMatrixMode(GL_COLOR);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
//	glDisable(GL_CONVOLUTION_2D);
//	glDisable(GL_COLOR_TABLE);

	glutSwapBuffers();
}

auto main(int argc, char *argv[]) -> int
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowSize(800, 600);
	glutCreateWindow("Imaging Subset Sample");
	glutReshapeFunc(onResizeWindow);
	glutDisplayFunc(onRenderScene);
	
    int version = gladLoadGL();
    if(version == 0) {
        printf("Something went wrong!\n");
        exit(-1);
    }

    if (!GLAD_GL_VERSION_1_0) {
        printf("Your system doesn't support OpenGL >= 2!\n");
        return -1;
    }

    printf("OpenGL %s, GLSL %s\n",
           glGetString(GL_VERSION),
           glGetString(GL_SHADING_LANGUAGE_VERSION));

//	std::cout << GL_ARB_imaging << std::endl;
/*
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
*/

	setupRc();
	
	glutMainLoop();

	return EXIT_SUCCESS;
}
