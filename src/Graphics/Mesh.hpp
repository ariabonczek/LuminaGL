#ifndef MESH_HPP
#define MESH_HPP

#include "../Config.hpp"

NS_BEGIN

struct MeshData;

class Mesh
{
public:
	Mesh(MeshData& data);
	Mesh(const Mesh& mesh);
	~Mesh();

	Mesh& operator=(const Mesh& mesh);

	void Bind();

	void Draw();
private:
	uint vbo;
	uint vao;
	uint numVertices;
};

NS_END

#endif