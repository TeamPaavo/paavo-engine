#include "..\include\Triangle.h"

using namespace pv;
using namespace pv::Primitive;

Triangle::Triangle(float size, float x, float y, Window &window):
_win(window)
{
	_size = size;
	_x = x;
	_y = y;
	
	_vertices = {

	_x, _y, 1.0f, 1.0f, 1.0f,
	_x, _y + _size, 1.0f, 1.0f, 1.0f,
	_x + _size, _y + _size, 1.0f, 1.0f, 1.0f

	};

	_elements = {
		0, 1, 2
	};

	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, _vertices.size()* sizeof(float), &_vertices.front(), GL_DYNAMIC_DRAW);

	glGenBuffers(1, &_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _elements.size() * sizeof(unsigned int), &_elements.front(), GL_STATIC_DRAW);

	_posAttrib = glGetAttribLocation(_win.getShader(), "position");
	glEnableVertexAttribArray(_posAttrib);
	glVertexAttribPointer(_posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);

	_colAttrib = glGetAttribLocation(_win.getShader(), "color");
	glEnableVertexAttribArray(_colAttrib);
	glVertexAttribPointer(_colAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));


}

void Triangle::move(float x, float y)
{
	_x += x;
	_y += y;

	_vertices = {

		_x, _y, 1.0f, 1.0f, 1.0f,
		_x, _y + _size, 1.0f, 1.0f, 1.0f,
		_x + _size, _y + _size, 1.0f, 1.0f, 1.0f

	};

	
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferSubData(_vbo, 0, _vertices.size()*sizeof(float), &_vertices.at(0));
	glBindBuffer(GL_ARRAY_BUFFER,0);

}


void Triangle::draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);


	glEnableVertexAttribArray(_posAttrib);
	glVertexAttribPointer(_posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);

	glEnableVertexAttribArray(_colAttrib);
	glVertexAttribPointer(_colAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));

	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
}


Triangle::~Triangle()
{
	glDeleteBuffers(1, &_ebo);
	glDeleteBuffers(1, &_vbo);

}
