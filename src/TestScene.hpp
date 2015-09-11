#ifndef TESTSCENE_HPP
#define TESTSCENE_HPP

#include "LuminaGL.hpp"

using namespace LuminaGL;

class TestScene : public Scene
{
public:
	TestScene();
	~TestScene();

	void LoadAssets();
	void Update(float dt);
	void Draw();
	void UnloadAssets();
private:
	void MoveCamera(float dt);

	Camera camera;
	Mesh* mesh;
	Material* mat;

	Mesh* mesh2;
	Matrix world;
	Matrix world2;
};


#endif
