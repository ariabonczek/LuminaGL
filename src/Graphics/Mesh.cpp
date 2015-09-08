#include "Mesh.hpp"
#include "Data.hpp"

NS_BEGIN

Mesh::Mesh(MeshData& data)
{
	numVertices = data.numVertices;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(MeshVertex) * numVertices, data.vertices, GL_STATIC_DRAW);

	// Setup MeshVertex data
	/* Position: */ glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 15, 0);
	/* Texcoord */  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 15, (void*)(sizeof(float) * 3));
	/* Color: */	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 15, (void*)(sizeof(float) * 5));
	/* Normal: */	glVertexAttribPointer(3, 3, GL_FLOAT, GL_TRUE,  sizeof(float) * 15, (void*)(sizeof(float) * 9));
	/* Tangent: */	glVertexAttribPointer(4, 3, GL_FLOAT, GL_TRUE,  sizeof(float) * 15, (void*)(sizeof(float) * 12));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);

}

Mesh::Mesh(const Mesh& mesh)
{
	vbo = mesh.vbo;
	vao = mesh.vao;
	numVertices = mesh.numVertices;
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &vbo);
}

Mesh& Mesh::operator=(const Mesh& mesh)
{
	vbo = mesh.vbo;
	vao = mesh.vao;
	numVertices = mesh.numVertices;
	return *this;
}

void Mesh::Bind()
{
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void Mesh::Draw()
{
	glDrawArrays(GL_TRIANGLES, 0, numVertices);
}

NS_END