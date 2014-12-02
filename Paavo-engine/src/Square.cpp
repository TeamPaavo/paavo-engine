#include "../include/Square.h"

using namespace pv;
using namespace pv::Primitive;

Square::Square(float size, float x, float y, Window &window)
:_win(window)
{
	_size = size;
	_x = x;
	_y = y;
	_offX = 0;
	_offY = 0;
	_a = 1.0f;
	_r = 1.0f;
	_g = 1.0f;
	_b = 1.0f;

	_vertices = {

		_x, _y, 0.0f, 0.0f, 0.0f,
		_x, _y + _size, 0.0f, 0.0f, 0.0f,
		_x + size, _y + _size, 0.0f, 0.0f, 0.0f,
		_x + size, _y, 0.0f, 0.0f, 0.0f

	};

	_elements = {
		0, 1, 2,
		0, 2, 3
	};

	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(float), &_vertices.front(), GL_STATIC_DRAW);

	glGenBuffers(1, &_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _elements.size() * sizeof(unsigned int), &_elements.front(), GL_STATIC_DRAW);

	// Specify the layout of the vertex data
	_posAttrib = glGetAttribLocation(_win.getShader("colorshader"), "position");
	glEnableVertexAttribArray(_posAttrib);
	glVertexAttribPointer(_posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);

	_colAttrib = glGetAttribLocation(_win.getShader("colorshader"), "color");
	glEnableVertexAttribArray(_colAttrib);
	glVertexAttribPointer(_colAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));

	_colUnif = glGetUniformLocation(_win.getShader("colorshader"), "unifcolor");
	assert(_colUnif >= 0);
	glUniform3f(_colUnif, 1.0f, 1.0f,1.0f);

	_alphaUnif = glGetUniformLocation(_win.getShader("colorshader"), "unifalpha");
	assert(_alphaUnif >= 0);
	glUniform1f(_alphaUnif, 1.0f);


	_offsetUnif = glGetUniformLocation(_win.getShader("colorshader"), "offset");
	assert(_offsetUnif >= 0);
	glUniform3f(_offsetUnif, 0.0f, 0.0f,0.0f);

}

void Square::move(float x, float y)
{
	_offX += x;
	_offY += y;
}

void Square::setPosition(float x, float y)
{
	_offX = x-_x;
	_offY = y-_y;
}

void Square::setColor(float r, float g, float b)
{
	_r = r;
	_g = g;
	_b = b;
}

void Square::setAlpha(float a)
{
	_a = a;
}


void Square::draw()
{
	_win.use("colorshader");
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);

	glEnableVertexAttribArray(_posAttrib);
	glVertexAttribPointer(_posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);

	glEnableVertexAttribArray(_colAttrib);
	glVertexAttribPointer(_colAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));

	glUniform2f(_offsetUnif, _offX, _offY);
	glUniform3f(_colUnif, _r, _g, _b);
	glUniform1f(_alphaUnif, _a);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}


Square::~Square()
{
	glDeleteBuffers(1, &_ebo);
	glDeleteBuffers(1, &_vbo);

}
