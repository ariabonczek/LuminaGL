#include "TestScene.hpp"

TestScene::TestScene()
{}

TestScene::~TestScene()
{}

void TestScene::LoadAssets()
{
	camera.Initialize();

	mesh = new Mesh(MeshBuilder::CreateCube(0.5f, Color::Red));

	mat = new Material();
	mat->LoadShader("Shaders/default.vert", ShaderType::Vertex);
	mat->LoadShader("Shaders/default.frag", ShaderType::Fragment);

	camera.SetPosition(Vector3(0.0f, 0.0f, -10.0f));
	world = Matrix::Identity;
}

void TestScene::Update(float dt)
{
	MoveCamera(dt);

	if (camera.IsDirty())
	{
		camera.UpdateViewMatrix();
	}
	
	world = world * Matrix::CreateFromQuaternion(Quaternion::CreateFromAxisAngle(Vector3::Up, dt * 100.0));

	mat->SetFloat4x4("model", world);
	mat->SetFloat4x4("view", camera.GetView());
	mat->SetFloat4x4("projection", camera.GetProjection());
}

void TestScene::Draw()
{
	mat->Bind();

	mesh->Draw();
}

void TestScene::UnloadAssets()
{
	delete mesh;
	mesh = nullptr;
}

void TestScene::MoveCamera(float dt)
{
	float speed = 10.0f * dt;
	if(Input::GetKey(GLFW_KEY_W))
	{
		camera.MoveForward(speed);
	}
	else if (Input::GetKey(GLFW_KEY_S))
	{
		camera.MoveForward(-speed);
	}

	if (Input::GetKey(GLFW_KEY_A))
	{
		camera.MoveRight(-speed);
	}
	else if (Input::GetKey(GLFW_KEY_D))
	{
		camera.MoveRight(speed);
	}

	speed *= 5.0f;

	if (Input::GetKey(GLFW_KEY_UP))
	{
		camera.Pitch(-speed);
	}
	else if (Input::GetKey(GLFW_KEY_DOWN))
	{
		camera.Pitch(speed);
	}

	if (Input::GetKey(GLFW_KEY_LEFT))
	{
		camera.RotateY(-speed);
	}
	else if (Input::GetKey(GLFW_KEY_RIGHT))
	{
		camera.RotateY(speed);
	}
}