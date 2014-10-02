#include "..\include\GLContext.h"

using namespace pv;

GLContext::GLContext()
{

}


GLContext::~GLContext()
{
}

void GLContext::init(HWND handle)
{
	_winHandle = handle;
	// Device hande
	_hDc = GetDC(_winHandle);

	// Set pixeformat data
	_pfd.nSize = sizeof(_pfd);
	_pfd.nVersion = 1;
	_pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
	_pfd.iPixelType = PFD_TYPE_RGBA;
	_pfd.cColorBits = 24;
	_pfd.cDepthBits = 24;

	_pixelFormat = ChoosePixelFormat(_hDc, &_pfd);
	SetPixelFormat(_hDc, _pixelFormat, &_pfd);

	// Create OpenGL context
	_hGlrc = wglCreateContext(_hDc);
	wglMakeCurrent(_hDc, _hGlrc);

	glewInit();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_CULL_FACE);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	_defaultShader.load("shaders/vertexshader.glsl", "shaders/fragmentshader.glsl");
	_defaultShader.use();
}

void GLContext::clearColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLContext::render()
{
	float vertices[] = {
		0.0f, 0.5f,
		-0.5f, -0.5f,
		0.5f, -0.5f
	};

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GLint posAttrib = glGetAttribLocation(_defaultShader.getProgram(), "position");
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(posAttrib);

	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void GLContext::swap()
{
	SwapBuffers(_hDc);
}

void GLContext::clean()
{
	wglMakeCurrent(_hDc, nullptr);
	wglDeleteContext(_hGlrc);
}