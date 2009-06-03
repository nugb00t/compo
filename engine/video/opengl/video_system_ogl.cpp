#include "stdafx.h"

// glew - before opengl
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/wglew.h>
// opengl
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glaux.h>
#pragma comment(lib, "glaux.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "opengl32.lib")

#include "window/window.h"

#include "video/mesh.h"

#include "video_system_ogl.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

VideoSystemOGL::VideoSystemOGL()
: context_(0) {}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

VideoSystemOGL::~VideoSystemOGL() {
	shutdown();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VideoSystemOGL::clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// important: screws up ATI rendering if disabled
	assert(glGetError() == GL_NO_ERROR);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool VideoSystemOGL::choosePixelFormat(BYTE colorBits, BYTE alphaBits, BYTE depthBits, BYTE stencilBits, BYTE samples)
{
	UINT numFormats;
	float fAttributes[] = {0, 0};

	int iAttributes[] = { 
		WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
		WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
		WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
		WGL_COLOR_BITS_ARB, colorBits,
		WGL_ALPHA_BITS_ARB, alphaBits,
		WGL_DEPTH_BITS_ARB, depthBits,
		WGL_STENCIL_BITS_ARB, stencilBits,
		WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
		WGL_SAMPLE_BUFFERS_ARB, GL_TRUE,
		WGL_SAMPLES_ARB, samples,
		0, 0};

	assert(wglChoosePixelFormatARB);

	int format;
	const bool ok = wglChoosePixelFormatARB(Window::get().context(), iAttributes, fAttributes, 1, &format, &numFormats) != 0 && numFormats > 0;

#ifdef DEBUG
	if (!ok) {
		TCHAR buffer[1024];
		DWORD msgLength = ::FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, ::GetLastError(), 0, buffer, sizeof(buffer), NULL);
		assert(msgLength);
	}
#endif

	return ok;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VideoSystemOGL::drawMesh(const Mesh& mesh) {
	// tmp
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glShadeModel(GL_SMOOTH);
	// tmp

	assert(mesh.getIndexCount() > 0 && mesh.getVerticeCount() > 0);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(Vertice), &mesh.getVerticeArray()[0].point);

	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, sizeof(Vertice), &mesh.getVerticeArray()[0].normal);

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertice), &mesh.getVerticeArray()[0].uv);

	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh.getIndexCount()), GL_UNSIGNED_INT, mesh.getIndexArray());
	assert(glGetError() == GL_NO_ERROR);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	assert(glGetError() == GL_NO_ERROR);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VideoSystemOGL::flush() {
	glFlush();
	assert(glGetError() == GL_NO_ERROR);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool VideoSystemOGL::init() {
	glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
	glClearDepth(1.0f);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	// defaults
	glDepthFunc(GL_LEQUAL);

	assert(GLEW_ARB_multitexture);

	glEnable(GL_MULTISAMPLE);
	glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
	
	return glGetError() == GL_NO_ERROR;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VideoSystemOGL::reshape(int width, int height) {
	glViewport(0, 0, width, height);
	aspect_ = static_cast<float>(width) / height;
	assert(glGetError() == GL_NO_ERROR);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VideoSystemOGL::setOrthogonalView() {
	GLfloat halfAspect = aspect_ / 2.0f;
	gluOrtho2D(-halfAspect, halfAspect, -0.5, 0.5);
	assert(glGetError() == GL_NO_ERROR);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VideoSystemOGL::shutdown() {
	if (context_) {
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(context_);
		context_ = NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool VideoSystemOGL::startup() {
	if (Window::get().choosePixelFormat(24, 8, 24, 0) &&
		(context_ = wglCreateContext(Window::get().context())) != 0 &&
		wglMakeCurrent(Window::get().context(), context_) &&
		glewInit() == GLEW_OK &&
		choosePixelFormat(24, 8, 24, 0, 2)) 
	{
		return true;
	} else {
		shutdown();
		assert(false);
		return false;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
void VideoSystemOGL::tex2d(const int level, const int border, const Image& image) {
	GLint format = GL_BGRA_EXT;
	GLint components = GL_RGB8;

	switch (image.depth()) {
		case 32: 
			format = GL_BGRA_EXT;
			components = GL_RGBA8;
			break;
		case 24:
			format = GL_BGR_EXT;
			components = GL_RGB8;
			break;
		case 8:
			format = GL_LUMINANCE;
			components = GL_LUMINANCE8;
			break;
		default:
			assert(false);
	}

	//glTexImage2D(GL_PROXY_TEXTURE_2D, level, components, image.width(), image.height(), border, format, GL_UNSIGNED_BYTE, image.data());
	glTexImage2D(GL_TEXTURE_2D, level, components, image.width(), image.height(), border, format, GL_UNSIGNED_BYTE, image.data());
	checkForError();
}
*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

