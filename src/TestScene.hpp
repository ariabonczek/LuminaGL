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

	bool polygonFlag;

	Camera camera;
	Mesh* mesh;
	Material* mat;

	Matrix world;
};


#endif
