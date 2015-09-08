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

	//static Mesh CreateSphere(float radius, uint numSubdivisions, Color color = Color::Gray);
	//static Mesh CreateCube(float size, Color color = Color::Gray);
	//static Mesh CreateCylinder(float radius, float height, uint numSubdivisions, Color color = Color::Gray);
	//static Mesh CreateCone(float radius, float height, uint numSubdivisions, Color color = Color::Gray);
	//static Mesh CreateTube(float outerRadius, float innerRadius, float height, uint numSubdivisions, Color color = Color::Gray);
	//static Mesh CreateTorus(float outerRadius, float innerRadius, uint numSubdivisions, Color color = Color::Gray);
private:
	MeshBuilder();
};

NS_END

#endif