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
	torus = new Mesh(MeshBuilder::CreateTorus(1.0f, 0.3f, 20, Color::Cyan));

	mat = new Material();
	mat->LoadShader("Shaders/default.vert", ShaderType::Vertex);
	mat->LoadShader("Shaders/default.frag", ShaderType::Fragment);

	camera.SetPosition(Vector3(0.0f, 0.0f, -10.0f));

	objects.push_back(new GameObject("Cube", cube, mat));
	objects.push_back(new GameObject("Sphere", sphere, mat));
	objects.push_back(new GameObject("Cylinder", cylinder, mat));
	objects.push_back(new GameObject("Cone", cone, mat));
	objects.push_back(new GameObject("Tube", tube, mat));
	objects.push_back(new GameObject("Torus", torus, mat));

	toDraw = objects[0];

	std::cout << "Press 1 through 6 to swap between different mesh primitives." << std::endl;
	std::cout << "1 - Cube" << std::endl;
	std::cout << "2 - Sphere" << std::endl;
	std::cout << "3 - Cylinder" << std::endl;
	std::cout << "4 - Cone" << std::endl;
	std::cout << "5 - Tube" << std::endl;
	std::cout << "6 - Torus" << std::endl;
	std::cout << "Press space to swap between fill and line polygon modes" << std::endl;
	std::cout << "Move the camera with WASD, rotate it with Up/Down/Left/Right, or by holding alt and using the mouse." << std::endl;
}

void TestScene::Update(float dt)
{
	MoveCamera(dt);

	if (Input::GetKeyDown(GLFW_KEY_SPACE))
	{
		polygonFlag ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		polygonFlag = !polygonFlag;
	}

	if (Input::GetKeyDown(GLFW_KEY_1)){ toDraw = objects[0]; }
	if (Input::GetKeyDown(GLFW_KEY_2)){ toDraw = objects[1]; }
	if (Input::GetKeyDown(GLFW_KEY_3)){ toDraw = objects[2]; }
	if (Input::GetKeyDown(GLFW_KEY_4)){ toDraw = objects[3]; }
	if (Input::GetKeyDown(GLFW_KEY_5)){ toDraw = objects[4]; }
	if (Input::GetKeyDown(GLFW_KEY_6)){ toDraw = objects[5]; }

	if (camera.IsDirty())
	{
		camera.UpdateViewMatrix();
	}

	for (uint i = 0; i < objects.size(); i++)
	{
		objects[i]->GetTransform()->Rotate(Quaternion::CreateFromAxisAngle(Vector3::Up, dt * 20.0f));
		objects[i]->Update(dt);
	}
	
	mat->SetFloat4x4("view", camera.GetView());
	mat->SetFloat4x4("projection", camera.GetProjection());
	mat->SetFloat3("viewPos", camera.GetPosition());
}

void TestScene::Draw()
{
	mat->Bind();

	toDraw->GetMaterial()->SetFloat4x4("model", toDraw->GetTransform()->GetWorldMatrix());
	toDraw->GetMaterial()->SetFloat4x4("modelInverseTranspose", Matrix::Transpose(Matrix::Inverse(toDraw->GetTransform()->GetWorldMatrix())));
	toDraw->GetMesh()->Draw();
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
	delete tube;
	delete torus;
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
		diff = diff * 0.25f;
		camera.RotateY(diff.x);
		camera.Pitch(diff.y);
	}
}