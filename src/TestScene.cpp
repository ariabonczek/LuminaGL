#include "TestScene.hpp"

TestScene::TestScene()
{}

TestScene::~TestScene()
{}

void TestScene::LoadAssets()
{
	MeshVertex vertices[3] = 
	{
		{ Vector3(0.0f, 0.5f, 0.0f), Vector2(0.0f, 0.0f), Color(0.0f, 1.0f, 1.0f, 1.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f) },
		{ Vector3(0.5f, -0.5f, 0.0f), Vector2(0.0f, 0.0f), Color(1.0f, 1.0f, 0.0f, 1.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f) },
		{ Vector3(-0.5f, -0.5f, 0.0f), Vector2(0.0f, 0.0f), Color(1.0f, 0.0f, 1.0f, 1.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f) }
	};
	MeshData data;
	data.vertices = vertices;
	data.numVertices = 3;

	mesh = new Mesh(data);

	mat = new Material();
	mat->LoadShader("Shaders/default.vert", ShaderType::Vertex);
	mat->LoadShader("Shaders/default.frag", ShaderType::Fragment);

	std::cout << sizeof(MeshVertex) << std::endl;
}

void TestScene::Update(float dt)
{

}

void TestScene::Draw()
{
	mat->Bind();
	mesh->Bind();
	mesh->Draw();
}

void TestScene::UnloadAssets()
{
	delete mesh;
	mesh = nullptr;
}