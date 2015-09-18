#include "TestScene.hpp"
#include "Utility\Timer.hpp"
#include <time.h>
#include <random>

TestScene::TestScene()
{}

TestScene::~TestScene()
{}

void TestScene::LoadAssets()
{
	camera.Initialize();
	
	cube = new Mesh(MeshBuilder::CreateCube(1.0f, Color::Red));
	sphere = new Mesh(MeshBuilder::CreateSphere(1.0f, 3, Color::Green));
	cylinder = new Mesh(MeshBuilder::CreateCylinder(1.0f, 1.0f, 25, 3, Color::Blue));
	cone = new Mesh(MeshBuilder::CreateCone(1.0f, 1.0f, 25, 3, Color::Yellow));
	tube = new Mesh(MeshBuilder::CreateTube(1.0f, 0.7f, 1.0f, 25, 3, Color::Red));

	mat = new Material();
	mat->LoadShader("Shaders/default.vert", ShaderType::Vertex);
	mat->LoadShader("Shaders/default.frag", ShaderType::Fragment);

	camera.SetPosition(Vector3(0.0f, 0.0f, -10.0f));

	objects.push_back(new GameObject("Sphere", tube, mat));
}

void TestScene::Update(float dt)
{
	MoveCamera(dt);

	if (Input::GetKeyDown(GLFW_KEY_SPACE))
	{
		polygonFlag ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		polygonFlag = !polygonFlag;
	}

	if (camera.IsDirty())
	{
		camera.UpdateViewMatrix();
	}

	for (uint i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt);
	}
	
	mat->SetFloat4x4("view", camera.GetView());
	mat->SetFloat4x4("projection", camera.GetProjection());
	mat->SetFloat3("viewPos", camera.GetPosition());
}

void TestScene::Draw()
{
	mat->Bind();

	for (uint i = 0; i < objects.size(); i++)
	{
		objects[i]->GetMaterial()->SetFloat4x4("model", objects[i]->GetTransform()->GetWorldMatrix());
		objects[i]->GetMaterial()->SetFloat4x4("modelInverseTranspose", Matrix::Transpose(Matrix::Inverse(objects[i]->GetTransform()->GetWorldMatrix())));
		objects[i]->GetMesh()->Draw();
	}
}

void TestScene::UnloadAssets()
{
	for (GameObject* g : objects)
		delete g;

	delete mat;
	mat = nullptr;
	
	delete cube;
	delete sphere;
	delete cylinder;
	delete cone;
}

void TestScene::MoveCamera(float dt)
{
	pMousePosition = mousePosition;
	mousePosition = Input::GetMousePosition();

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

	speed *= 10.0f;

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
	
	// Mouse controls
	if (Input::GetKey(GLFW_KEY_LEFT_ALT))
	{
		Vector2 diff = mousePosition - pMousePosition;

		camera.RotateY(diff.x);
		camera.Pitch(diff.y);
	}
}