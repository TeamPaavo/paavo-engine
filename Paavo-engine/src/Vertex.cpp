#include "..\include\Vertex.h"

using namespace pv;

Vertex::Vertex()
{

}

Vertex::Vertex(const glm::vec3& pos, const glm::vec4& col, const glm::vec2& tex)
{
	position = pos;
	colour = col;
	texture = tex;
}


Vertex::~Vertex()
{
}
