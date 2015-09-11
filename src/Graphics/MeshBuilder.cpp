#include "MeshBuilder.hpp"

NS_BEGIN

MeshBuilder::~MeshBuilder()
{

}

//Mesh MeshBuilder::CreateSphere(float radius, uint numSubdivisions, Color color)
//{
//
//}
//

MeshData MeshBuilder::CreateCube(float size, Color color)
{
	MeshData data;

	data.vertices.resize(0);
	data.indices.resize(0);

	MeshVertex cVert;
	cVert.color = color;
	///
	// MeshVertex order when facing quad: bottom left, top left, top right, bottom right
	///

	//Front
	cVert.position = Vector3(-size, -size, -size);
	cVert.normal = Vector3(0.0f, 0.0f, -1.0f);
	cVert.tangent = Vector3(1.0f, 0.0f, 0.0f);
	cVert.texcoord = Vector2(0.0f, 1.0f);
	data.vertices.push_back(cVert);

	cVert.position = Vector3(-size, size, -size);
	cVert.normal = Vector3(0.0f, 0.0f, -1.0f);
	cVert.tangent = Vector3(1.0f, 0.0f, 0.0f);
	cVert.texcoord = Vector2(0.0f, 0.0f);
	data.vertices.push_back(cVert);

	cVert.position = Vector3(size, size, -size);
	cVert.normal = Vector3(0.0f, 0.0f, -1.0f);
	cVert.tangent = Vector3(1.0f, 0.0f, 0.0f);
	cVert.texcoord = Vector2(1.0f, 0.0f);
	data.vertices.push_back(cVert);

	cVert.position = Vector3(size, -size, -size);
	cVert.normal = Vector3(0.0f, 0.0f, -1.0f);
	cVert.tangent = Vector3(1.0f, 0.0f, 0.0f);
	cVert.texcoord = Vector2(1.0f, 1.0f);
	data.vertices.push_back(cVert);

	// Back
	cVert.position = Vector3(-size, -size, size);
	cVert.normal = Vector3(0.0f, 0.0f, 1.0f);
	cVert.tangent = Vector3(1.0f, 0.0f, 0.0f);
	cVert.texcoord = Vector2(0.0f, 1.0f);
	data.vertices.push_back(cVert);

	cVert.position = Vector3(-size, size, size);
	cVert.normal = Vector3(0.0f, 0.0f, 1.0f);
	cVert.tangent = Vector3(1.0f, 0.0f, 0.0f);
	cVert.texcoord = Vector2(0.0f, 0.0f);
	data.vertices.push_back(cVert);

	cVert.position = Vector3(size, size, size);
	cVert.normal = Vector3(0.0f, 0.0f, 1.0f);
	cVert.tangent = Vector3(1.0f, 0.0f, 0.0f);
	cVert.texcoord = Vector2(1.0f, 0.0f);
	data.vertices.push_back(cVert);

	cVert.position = Vector3(size, -size, size);
	cVert.normal = Vector3(0.0f, 0.0f, 1.0f);
	cVert.tangent = Vector3(1.0f, 0.0f, 0.0f);
	cVert.texcoord = Vector2(1.0f, 1.0f);
	data.vertices.push_back(cVert);

	// Left
	cVert.position = Vector3(-size, -size, size);
	cVert.normal = Vector3(-1.0f, 0.0f, 0.0f);
	cVert.tangent = Vector3(0.0f, 0.0f, -1.0f);
	cVert.texcoord = Vector2(0.0f, 1.0f);
	data.vertices.push_back(cVert);

	cVert.position = Vector3(-size, size, size);
	cVert.normal = Vector3(-1.0f, 0.0f, 0.0f);
	cVert.tangent = Vector3(0.0f, 0.0f, -1.0f);
	cVert.texcoord = Vector2(0.0f, 0.0f);
	data.vertices.push_back(cVert);

	cVert.position = Vector3(-size, size, -size);
	cVert.normal = Vector3(-1.0f, 0.0f, 0.0f);
	cVert.tangent = Vector3(0.0f, 0.0f, -1.0f);
	cVert.texcoord = Vector2(1.0f, 0.0f);
	data.vertices.push_back(cVert);

	cVert.position = Vector3(-size, -size, -size);
	cVert.normal = Vector3(-1.0f, 0.0f, 0.0f);
	cVert.tangent = Vector3(0.0f, 0.0f, -1.0f);
	cVert.texcoord = Vector2(1.0f, 1.0f);
	data.vertices.push_back(cVert);

	// Right
	cVert.position = Vector3(size, -size, -size);
	cVert.normal = Vector3(1.0f, 0.0f, 0.0f);
	cVert.tangent = Vector3(0.0f, 0.0f, -1.0f);
	cVert.texcoord = Vector2(0.0f, 1.0f);
	data.vertices.push_back(cVert);

	cVert.position = Vector3(size, size, -size);
	cVert.normal = Vector3(1.0f, 0.0f, 0.0f);
	cVert.tangent = Vector3(0.0f, 0.0f, -1.0f);
	cVert.texcoord = Vector2(0.0f, 0.0f);
	data.vertices.push_back(cVert);

	cVert.position = Vector3(size, size, size);
	cVert.normal = Vector3(1.0f, 0.0f, 0.0f);
	cVert.tangent = Vector3(0.0f, 0.0f, -1.0f);
	cVert.texcoord = Vector2(1.0f, 0.0f);
	data.vertices.push_back(cVert);

	cVert.position = Vector3(size, -size, size);
	cVert.normal = Vector3(1.0f, 0.0f, 0.0f);
	cVert.tangent = Vector3(0.0f, 0.0f, -1.0f);
	cVert.texcoord = Vector2(1.0f, 1.0f);
	data.vertices.push_back(cVert);

	// Top
	cVert.position = Vector3(-size, size, -size);
	cVert.normal = Vector3(0.0f, 1.0f, 0.0f);
	cVert.tangent = Vector3(1.0f, 0.0f, 0.0f);
	cVert.texcoord = Vector2(0.0f, 1.0f);
	data.vertices.push_back(cVert);

	cVert.position = Vector3(-size, size, size);
	cVert.normal = Vector3(0.0f, 1.0f, 0.0f);
	cVert.tangent = Vector3(1.0f, 0.0f, 0.0f);
	cVert.texcoord = Vector2(0.0f, 0.0f);
	data.vertices.push_back(cVert);

	cVert.position = Vector3(size, size, size);
	cVert.normal = Vector3(0.0f, 1.0f, 0.0f);
	cVert.tangent = Vector3(1.0f, 0.0f, 0.0f);
	cVert.texcoord = Vector2(1.0f, 0.0f);
	data.vertices.push_back(cVert);

	cVert.position = Vector3(size, size, -size);
	cVert.normal = Vector3(0.0f, 1.0f, 0.0f);
	cVert.tangent = Vector3(1.0f, 0.0f, 0.0f);
	cVert.texcoord = Vector2(1.0f, 1.0f);
	data.vertices.push_back(cVert);

	// Bottom
	cVert.position = Vector3(-size, -size, -size);
	cVert.normal = Vector3(0.0f, -1.0f, 0.0f);
	cVert.tangent = Vector3(1.0f, 0.0f, 0.0f);
	cVert.texcoord = Vector2(0.0f, 1.0f);
	data.vertices.push_back(cVert);

	cVert.position = Vector3(-size, -size, size);
	cVert.normal = Vector3(0.0f, -1.0f, 0.0f);
	cVert.tangent = Vector3(1.0f, 0.0f, 0.0f);
	cVert.texcoord = Vector2(0.0f, 0.0f);
	data.vertices.push_back(cVert);

	cVert.position = Vector3(size, -size, size);
	cVert.normal = Vector3(0.0f, -1.0f, 0.0f);
	cVert.tangent = Vector3(1.0f, 0.0f, 0.0f);
	cVert.texcoord = Vector2(1.0f, 0.0f);
	data.vertices.push_back(cVert);

	cVert.position = Vector3(size, -size, -size);
	cVert.normal = Vector3(0.0f, -1.0f, 0.0f);
	cVert.tangent = Vector3(1.0f, 0.0f, 0.0f);
	cVert.texcoord = Vector2(1.0f, 1.0f);
	data.vertices.push_back(cVert);

	// INDICES
	data.indices.push_back(0);
	data.indices.push_back(1);
	data.indices.push_back(3);
	data.indices.push_back(3);
	data.indices.push_back(1);
	data.indices.push_back(2);

	data.indices.push_back(4);
	data.indices.push_back(6);
	data.indices.push_back(5);
	data.indices.push_back(6);
	data.indices.push_back(4);
	data.indices.push_back(7);

	data.indices.push_back(8);
	data.indices.push_back(9);
	data.indices.push_back(10);
	data.indices.push_back(10);
	data.indices.push_back(11);
	data.indices.push_back(8);

	data.indices.push_back(12);
	data.indices.push_back(13);
	data.indices.push_back(14);
	data.indices.push_back(14);
	data.indices.push_back(15);
	data.indices.push_back(12);

	data.indices.push_back(16);
	data.indices.push_back(17);
	data.indices.push_back(18);
	data.indices.push_back(18);
	data.indices.push_back(19);
	data.indices.push_back(16);

	data.indices.push_back(20);
	data.indices.push_back(22);
	data.indices.push_back(21);
	data.indices.push_back(20);
	data.indices.push_back(23);
	data.indices.push_back(22);

	return data;
}

//Mesh MeshBuilder::CreateCylinder(float radius, float size, uint numSubdivisions, Color color)
//{
//
//}
//
//Mesh MeshBuilder::CreateCone(float radius, float size, uint numSubdivisions, Color color)
//{
//
//}
//
//Mesh MeshBuilder::CreateTube(float outerRadius, float innerRadius, float size, uint numSubdivisions, Color color)
//{
//
//}
//
//Mesh MeshBuilder::CreateTorus(float outerRadius, float innerRadius, uint numSubdivisions, Color color)
//{
//
//}

MeshBuilder::MeshBuilder()
{}

NS_END