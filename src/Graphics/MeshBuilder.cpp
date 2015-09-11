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
	uint v = 0, i = 0;

	data.vertices.resize(24);
	data.indices.resize(36);

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
	data.vertices[v++] = cVert;

	cVert.position = Vector3(-size, size, -size);
	cVert.normal = Vector3(0.0f, 0.0f, -1.0f);
	cVert.tangent = Vector3(1.0f, 0.0f, 0.0f);
	cVert.texcoord = Vector2(0.0f, 0.0f);
	data.vertices[v++] = cVert;

	cVert.position = Vector3(size, size, -size);
	cVert.normal = Vector3(0.0f, 0.0f, -1.0f);
	cVert.tangent = Vector3(1.0f, 0.0f, 0.0f);
	cVert.texcoord = Vector2(1.0f, 0.0f);
	data.vertices[v++] = cVert;

	cVert.position = Vector3(size, -size, -size);
	cVert.normal = Vector3(0.0f, 0.0f, -1.0f);
	cVert.tangent = Vector3(1.0f, 0.0f, 0.0f);
	cVert.texcoord = Vector2(1.0f, 1.0f);
	data.vertices[v++] = cVert;

	// Back
	cVert.position = Vector3(-size, -size, size);
	cVert.normal = Vector3(0.0f, 0.0f, 1.0f);
	cVert.tangent = Vector3(1.0f, 0.0f, 0.0f);
	cVert.texcoord = Vector2(0.0f, 1.0f);
	data.vertices[v++] = cVert;

	cVert.position = Vector3(-size, size, size);
	cVert.normal = Vector3(0.0f, 0.0f, 1.0f);
	cVert.tangent = Vector3(1.0f, 0.0f, 0.0f);
	cVert.texcoord = Vector2(0.0f, 0.0f);
	data.vertices[v++] = cVert;

	cVert.position = Vector3(size, size, size);
	cVert.normal = Vector3(0.0f, 0.0f, 1.0f);
	cVert.tangent = Vector3(1.0f, 0.0f, 0.0f);
	cVert.texcoord = Vector2(1.0f, 0.0f);
	data.vertices[v++] = cVert;

	cVert.position = Vector3(size, -size, size);
	cVert.normal = Vector3(0.0f, 0.0f, 1.0f);
	cVert.tangent = Vector3(1.0f, 0.0f, 0.0f);
	cVert.texcoord = Vector2(1.0f, 1.0f);
	data.vertices[v++] = cVert;

	// Left
	cVert.position = Vector3(-size, -size, size);
	cVert.normal = Vector3(-1.0f, 0.0f, 0.0f);
	cVert.tangent = Vector3(0.0f, 0.0f, -1.0f);
	cVert.texcoord = Vector2(0.0f, 1.0f);
	data.vertices[v++] = cVert;

	cVert.position = Vector3(-size, size, size);
	cVert.normal = Vector3(-1.0f, 0.0f, 0.0f);
	cVert.tangent = Vector3(0.0f, 0.0f, -1.0f);
	cVert.texcoord = Vector2(0.0f, 0.0f);
	data.vertices[v++] = cVert;

	cVert.position = Vector3(-size, size, -size);
	cVert.normal = Vector3(-1.0f, 0.0f, 0.0f);
	cVert.tangent = Vector3(0.0f, 0.0f, -1.0f);
	cVert.texcoord = Vector2(1.0f, 0.0f);
	data.vertices[v++] = cVert;

	cVert.position = Vector3(-size, -size, -size);
	cVert.normal = Vector3(-1.0f, 0.0f, 0.0f);
	cVert.tangent = Vector3(0.0f, 0.0f, -1.0f);
	cVert.texcoord = Vector2(1.0f, 1.0f);
	data.vertices[v++] = cVert;

	// Right
	cVert.position = Vector3(size, -size, -size);
	cVert.normal = Vector3(1.0f, 0.0f, 0.0f);
	cVert.tangent = Vector3(0.0f, 0.0f, -1.0f);
	cVert.texcoord = Vector2(0.0f, 1.0f);
	data.vertices[v++] = cVert;

	cVert.position = Vector3(size, size, -size);
	cVert.normal = Vector3(1.0f, 0.0f, 0.0f);
	cVert.tangent = Vector3(0.0f, 0.0f, -1.0f);
	cVert.texcoord = Vector2(0.0f, 0.0f);
	data.vertices[v++] = cVert;

	cVert.position = Vector3(size, size, size);
	cVert.normal = Vector3(1.0f, 0.0f, 0.0f);
	cVert.tangent = Vector3(0.0f, 0.0f, -1.0f);
	cVert.texcoord = Vector2(1.0f, 0.0f);
	data.vertices[v++] = cVert;

	cVert.position = Vector3(size, -size, size);
	cVert.normal = Vector3(1.0f, 0.0f, 0.0f);
	cVert.tangent = Vector3(0.0f, 0.0f, -1.0f);
	cVert.texcoord = Vector2(1.0f, 1.0f);
	data.vertices[v++] = cVert;

	// Top
	cVert.position = Vector3(-size, size, -size);
	cVert.normal = Vector3(0.0f, 1.0f, 0.0f);
	cVert.tangent = Vector3(1.0f, 0.0f, 0.0f);
	cVert.texcoord = Vector2(0.0f, 1.0f);
	data.vertices[v++] = cVert;

	cVert.position = Vector3(-size, size, size);
	cVert.normal = Vector3(0.0f, 1.0f, 0.0f);
	cVert.tangent = Vector3(1.0f, 0.0f, 0.0f);
	cVert.texcoord = Vector2(0.0f, 0.0f);
	data.vertices[v++] = cVert;

	cVert.position = Vector3(size, size, size);
	cVert.normal = Vector3(0.0f, 1.0f, 0.0f);
	cVert.tangent = Vector3(1.0f, 0.0f, 0.0f);
	cVert.texcoord = Vector2(1.0f, 0.0f);
	data.vertices[v++] = cVert;

	cVert.position = Vector3(size, size, -size);
	cVert.normal = Vector3(0.0f, 1.0f, 0.0f);
	cVert.tangent = Vector3(1.0f, 0.0f, 0.0f);
	cVert.texcoord = Vector2(1.0f, 1.0f);
	data.vertices[v++] = cVert;

	// Bottom
	cVert.position = Vector3(-size, -size, -size);
	cVert.normal = Vector3(0.0f, -1.0f, 0.0f);
	cVert.tangent = Vector3(1.0f, 0.0f, 0.0f);
	cVert.texcoord = Vector2(0.0f, 1.0f);
	data.vertices[v++] = cVert;

	cVert.position = Vector3(-size, -size, size);
	cVert.normal = Vector3(0.0f, -1.0f, 0.0f);
	cVert.tangent = Vector3(1.0f, 0.0f, 0.0f);
	cVert.texcoord = Vector2(0.0f, 0.0f);
	data.vertices[v++] = cVert;

	cVert.position = Vector3(size, -size, size);
	cVert.normal = Vector3(0.0f, -1.0f, 0.0f);
	cVert.tangent = Vector3(1.0f, 0.0f, 0.0f);
	cVert.texcoord = Vector2(1.0f, 0.0f);
	data.vertices[v++] = cVert;

	cVert.position = Vector3(size, -size, -size);
	cVert.normal = Vector3(0.0f, -1.0f, 0.0f);
	cVert.tangent = Vector3(1.0f, 0.0f, 0.0f);
	cVert.texcoord = Vector2(1.0f, 1.0f);
	data.vertices[v++] = cVert;

	// INDICES
	data.indices[i++] = (0);
	data.indices[i++] = (1);
	data.indices[i++] = (3);
	data.indices[i++] = (3);
	data.indices[i++] = (1);
	data.indices[i++] = (2);

	data.indices[i++] = (4);
	data.indices[i++] = (6);
	data.indices[i++] = (5);
	data.indices[i++] = (6);
	data.indices[i++] = (4);
	data.indices[i++] = (7);

	data.indices[i++] = (8);
	data.indices[i++] = (9);
	data.indices[i++] = (10);
	data.indices[i++] = (10);
	data.indices[i++] = (11);
	data.indices[i++] = (8);

	data.indices[i++] = (12);
	data.indices[i++] = (13);
	data.indices[i++] = (14);
	data.indices[i++] = (14);
	data.indices[i++] = (15);
	data.indices[i++] = (12);

	data.indices[i++] = (16);
	data.indices[i++] = (17);
	data.indices[i++] = (18);
	data.indices[i++] = (18);
	data.indices[i++] = (19);
	data.indices[i++] = (16);

	data.indices[i++] = (20);
	data.indices[i++] = (22);
	data.indices[i++] = (21);
	data.indices[i++] = (20);
	data.indices[i++] = (23);
	data.indices[i++] = (22);

	return data;
}

MeshData MeshBuilder::CreateCylinder(float radius, float height, uint axisDivisions, uint heightDivisions, Color color)
{
	MeshData data;

	uint v = 0, t = 0;
	uint numVerts = 2 + (axisDivisions * (heightDivisions + 1));
	uint numTris = 2 * axisDivisions + 2 * heightDivisions * axisDivisions;
	data.vertices.resize(numVerts);
	data.indices.resize(numTris * 3);

	height *= 0.5f;

	data.vertices[v++].position = Vector3::Up * -height;

	for (uint i = 0; i < axisDivisions; i++)
	{
		float theta = ((float)i / axisDivisions) * PI * 2;
		float x = cosf(theta) * radius;
		float z = sinf(theta) * radius;
		v = CreateVertexLineC(Vector3(x, -height, z), Vector3(x, height, z), heightDivisions, v, data.vertices);
	}

	data.vertices[v++].position = Vector3::Up * height;

	///
	// Indices
	///

	// bottom circle
	uint base = 1;
	for (uint i = 1; i <= axisDivisions; i++)
	{
		data.indices[t++] = 0;
		data.indices[t++] = base;
		data.indices[t++] = base + (heightDivisions + 1);

		base += heightDivisions + 1;
	}

	data.indices[t - 1] = 1;

	// rings
	for (uint i = 1; i <= heightDivisions ; i++)
	{
		t = CreateRing(axisDivisions, heightDivisions + 1, i, t, data.indices);
	}

	// Top circle
	for (uint i = 1; i <= axisDivisions; i++)
	{
		data.indices[t++] = (heightDivisions + 1) * i;
		data.indices[t++] = data.vertices.size() - 1;
		data.indices[t++] = (heightDivisions + 1) * i + (heightDivisions + 1);
	}

	data.indices[t - 1] = heightDivisions + 1;

	for (uint i = 0; i < data.vertices.size(); i++)
	{
		data.vertices[i].color = color;
	}

	return data;
}

uint MeshBuilder::CreateVertexLineC(Vector3 from, Vector3 to, uint steps, uint v, std::vector<MeshVertex>& vertices)
{
	for (int i = 0; i <= steps; i++)
	{
		vertices[v++].position = Vector3::Lerp(from, to, (float)i / steps);
	}
	return v;
}


MeshData MeshBuilder::CreateCone(float radius, float height, uint axisDivisions, uint heightDivisions, Color color)
{
	MeshData data;

	uint v = 0, t = 0;

	uint numVerts = 2 + (axisDivisions * heightDivisions);
	uint numTris = axisDivisions * ((2 * heightDivisions) - 1) + axisDivisions;
	data.vertices.resize(numVerts);
	data.indices.resize(numTris * 3);

	height *= 0.5f; // centering our cone at the origion

	///
	// Vertices
	///
	// bottom
	data.vertices[v++].position = Vector3::Up * -height;

	// rings
	for (uint i = 0; i < axisDivisions; i++)
	{
		float theta = ((float)i / axisDivisions) * PI * 2;
		float x = cosf(theta) * radius;
		float z = sinf(theta) * radius;
		v = CreateVertexLine(Vector3::Up * -height, Vector3(x, height, z), heightDivisions , v, data.vertices);
	}

	// top
	data.vertices[v++].position = Vector3::Up * height;


	///
	// Indices
	///
	// bottom "ring"
	uint nextAxis;
	for (uint i = 0; i < axisDivisions; i++)
	{
		nextAxis = i * heightDivisions;
		data.indices[t++] = 0;
		data.indices[t++] = nextAxis + 1;
		data.indices[t++] = nextAxis + heightDivisions + 1;
	}
	
	// Set the last value back to one
	data.indices[t - 1] = 1;

	// Remaining "rings"
	for (uint i = 1; i < heightDivisions; i++)
	{
		t = CreateRing(axisDivisions, heightDivisions, i, t, data.indices);
	}

	// Top circle
	for (uint i = 1; i <= axisDivisions; i++)
	{
		data.indices[t++] = heightDivisions * i;
		data.indices[t++] = data.vertices.size() - 1;
		data.indices[t++] = heightDivisions * i + heightDivisions;
	}

	data.indices[t - 1] = heightDivisions;

	for (uint i = 0; i < data.vertices.size(); i++)
	{
		data.vertices[i].color = color;
	}

	return data;
}

uint MeshBuilder::CreateRing(uint axisDivisions, uint heightDivisions, uint h, uint t, std::vector<uint>& indices)
{
	uint base = h;
	for (uint i = 0; i < axisDivisions; i++)
	{
		indices[t++] = base;					 // 1 6
		indices[t++] = base + 1;				 // 2 7
		indices[t++] = base + heightDivisions;	 // 6 11

		indices[t++] = base + heightDivisions; 		// 6 11
		indices[t++] = base + 1;					// 2 7
		indices[t++] = base + heightDivisions + 1;	// 7 12

		base += heightDivisions;			// 6 11
	}

	indices[t - 4] = h;
	indices[t - 3] = h;
	indices[t - 1] = h + 1;

	return t;
}


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