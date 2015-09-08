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
	uint vertexBuffer;
	uint vertexArray;
	uint indexBuffer;

	uint numVertices;
	uint numIndices;
};

NS_END

#endif