#include "..\include\Sprite.h"

#include <GL\glew.h>
#include <FreeImage.h>

#include "../include/TextureManager.h"

using namespace pv;

Sprite::Sprite(float x, float y, float width, float height, pv::Window& window)
	:_win(window)
{

	_x = x;
	_y = y;
	_offX = 0;
	_offY = 0;
	_width = width;
	_height = height;

	_vertices = {
		// x, y,   r, g, b,   u, v
		_x, _y, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		_x, _y + _height, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		_x + _width, _y + _height, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		_x + _width, _y, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
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
	_posAttrib = glGetAttribLocation(_win.getShader("textureshader"), "position");
	glEnableVertexAttribArray(_posAttrib);
	glVertexAttribPointer(_posAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), 0);

	_colAttrib = glGetAttribLocation(_win.getShader("textureshader"), "color");
	glEnableVertexAttribArray(_colAttrib);
	glVertexAttribPointer(_colAttrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));

	_texAttrib = glGetAttribLocation(_win.getShader("textureshader"), "texcoord");
	glEnableVertexAttribArray(_texAttrib);
	glVertexAttribPointer(_texAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat)));

	_offsetUnif = glGetUniformLocation(_win.getShader("textureshader"), "offset");
	assert(_offsetUnif >= 0);
	glUniform3f(_offsetUnif, 0.0f, 0.0f, 0.0f);

}

Sprite::~Sprite()
{
	glDeleteBuffers(1, &_ebo);
	glDeleteBuffers(1, &_vbo);

	glDeleteTextures(1, &_texId);
}

void Sprite::move(float x, float y)
{
	_offX += x;
	_offY += y;
}

void Sprite::setPosition(float x, float y)
{
	_offX = x - _x;
	_offY = y - _y;
}


void Sprite::setTexture(std::string filename)
{

	glActiveTexture(GL_TEXTURE0);
	_texId = TextureManager::getInstance()->load(filename);
	glUniform1i(glGetUniformLocation(_win.getShader("textureshader"), "tex"), 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

}

void Sprite::draw()
{
	_win.use("textureshader");
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);

	glEnableVertexAttribArray(_posAttrib);
	glVertexAttribPointer(_posAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), 0);

	glEnableVertexAttribArray(_colAttrib);
	glVertexAttribPointer(_colAttrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));

	glEnableVertexAttribArray(_texAttrib);
	glVertexAttribPointer(_texAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat)));

	glUniform2f(_offsetUnif, _offX, _offY);
	glUniform1i(glGetUniformLocation(_win.getShader("textureshader"), "tex"), 0);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}
