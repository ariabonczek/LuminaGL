#include "MeshBuilder.hpp"

NS_BEGIN

MeshBuilder::~MeshBuilder()
{

}

// Followed this tutorial: http://www.binpress.com/tutorial/creating-an-octahedron-sphere/162
MeshData MeshBuilder::CreateSphere(float radius, uint numSubdivisions, Color color)
{
	MeshData data;
	MeshVertex toAdd;

	numSubdivisions = std::max(0u, std::min(numSubdivisions, 7u));

	int resolution = 1 << numSubdivisions;
	data.vertices.resize((resolution + 1) * (resolution + 1) * 4 - (resolution * 2 - 1) * 3);
	data.indices.resize((1 << (numSubdivisions * 2 + 3)) * 3);

	CreateOctahedron(data.vertices, data.indices, resolution);

	for (uint i = 0; i < data.vertices.size(); ++i)
	{
		// Color
		data.vertices[i].color = color;
		// Position and Normals
		data.vertices[i].position.Normalize();
		data.vertices[i].normal = data.vertices[i].position;

		Vector3 p = Vector3::Multiply(data.vertices[i].position, radius);
		data.vertices[i].position = p;

		// UVs
		float theta = atan2(data.vertices[i].position.x, data.vertices[i].position.z);
		float phi = asinf(data.vertices[i].position.y);

		data.vertices[i].texcoord.x = theta / PI * 2;
		if (data.vertices[i].texcoord.x < 0.0f)
			data.vertices[i].texcoord.x += 1.0f;

		data.vertices[i].texcoord.y = phi / PI + 0.5f;

		// Tangents
		data.vertices[i].tangent.x = -radius*sinf(phi)*sinf(theta);
		data.vertices[i].tangent.y = 0.0f;
		data.vertices[i].tangent.z = +radius*cosf(phi)*cosf(theta);

		data.vertices[i].tangent.Normalize();
	}

	return data;
}

void MeshBuilder::CreateOctahedron(std::vector<MeshVertex>& vertices, std::vector<uint>& indices, uint resolution)
{
	uint v = 0, vBottom = 0, t = 0;

	Vector3 directions[4] =
	{
		-Vector3::Right,
		-Vector3::Forward,
		Vector3::Right,
		Vector3::Forward
	};

	for (uint i = 0; i < 4; i++)
	{
		vertices[v++].position = -Vector3::Up;
	}

	// bottom hemisphere
	for (uint i = 1; i <= resolution; i++)
	{
		float progress = (float)i / resolution;
		Vector3 from, to;
		vertices[v++].position = to = Vector3::Lerp(-Vector3::Up, Vector3::Forward, progress);
		for (uint d = 0; d < 4; d++)
		{
			from = to;
			to = Vector3::Lerp(-Vector3::Up, directions[d], progress);
			t = CreateLowerStrip(i, v, vBottom, t, indices);
			v = CreateVertexLine(from, to, i, v, vertices);
			vBottom += i > 1 ? (i - 1) : 1;
		}
		vBottom = v - 1 - i * 4;
	}

	// top hemisphere
	for (uint i = resolution - 1; i >= 1; i--)
	{
		float progress = (float)i / resolution;
		Vector3 from, to;
		vertices[v++].position = to = Vector3::Lerp(Vector3::Up, Vector3::Forward, progress);
		for (uint d = 0; d < 4; d++)
		{
			from = to;
			to = Vector3::Lerp(Vector3::Up, directions[d], progress);
			t = CreateUpperStrip(i, v, vBottom, t, indices);
			v = CreateVertexLine(from, to, i, v, vertices);
			vBottom += i + 1;
		}
		vBottom = v - 1 - i * 4;
	}

	for (uint i = 0; i < 4; i++)
	{
		indices[t++] = vBottom;
		indices[t++] = v;
		indices[t++] = ++vBottom;
		vertices[v++].position = Vector3::Up;
	}
}

uint MeshBuilder::CreateUpperStrip(uint steps, uint vTop, uint vBottom, uint t, std::vector<uint>& indices)
{
	indices[t++] = vBottom;
	indices[t++] = vTop - 1;
	indices[t++] = ++vBottom;
	for (int i = 1; i <= steps; i++)
	{
		indices[t++] = vTop - 1;
		indices[t++] = vTop;
		indices[t++] = vBottom;

		indices[t++] = vBottom;
		indices[t++] = vTop++;
		indices[t++] = ++vBottom;
	}

	return t;
}

uint MeshBuilder::CreateLowerStrip(uint steps, uint vTop, uint vBottom, uint t, std::vector<uint>& indices)
{
	for (uint i = 1; i < steps; i++)
	{
		indices[t++] = vBottom;
		indices[t++] = vTop - 1;
		indices[t++] = vTop;

		indices[t++] = vBottom++;
		indices[t++] = vTop++;
		indices[t++] = vBottom;
	}
	indices[t++] = vBottom;
	indices[t++] = vTop - 1;
	indices[t++] = vTop;

	return t;
}

uint MeshBuilder::CreateVertexLine(Vector3 from, Vector3 to, uint steps, uint v, std::vector<MeshVertex>& vertices)
{
	for (int i = 1; i <= steps; i++)
	{
		vertices[v++].position = Vector3::Lerp(from, to, (float)i / steps);
	}
	return v;
}

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