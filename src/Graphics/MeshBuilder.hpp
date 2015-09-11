#ifndef MESHBUILDER_HPP
#define MESHBUILDER_HPP

#include "../Config.hpp"
#include "Data.hpp"
#include "Mesh.hpp"

NS_BEGIN

class MeshBuilder
{
public:
	~MeshBuilder();

	static MeshData CreateSphere(float radius, uint numSubdivisions, Color color = Color::Gray);
	static MeshData CreateCube(float size, Color color = Color::Gray);
	static MeshData CreateCylinder(float radius, float height, uint numSubdivisions, Color color = Color::Gray);
	static MeshData CreateCone(float radius, float height, uint numSubdivisions, Color color = Color::Gray);
	static MeshData CreateTube(float outerRadius, float innerRadius, float height, uint numSubdivisions, Color color = Color::Gray);
	static MeshData CreateTorus(float outerRadius, float innerRadius, uint numSubdivisions, Color color = Color::Gray);
private:
	MeshBuilder();

	static void CreateOctahedron(std::vector<MeshVertex>& vertices, std::vector<uint>& indices, uint resolution);
	static uint CreateUpperStrip(uint steps, uint vTop, uint vBottom, uint t, std::vector<uint>& indices);
	static uint CreateLowerStrip(uint steps, uint vTop, uint vBottom, uint t, std::vector<uint>& indices);
	static uint CreateVertexLine(Vector3 from, Vector3 to, uint steps, uint v, std::vector<MeshVertex>& vertices);
};

NS_END

#endif