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
	std::vector<GameObject*> objects;

	Mesh* cube;
	Mesh* sphere;
	Mesh* cylinder;
	Mesh* cone;
	Mesh* tube;
	Material* mat;

	Vector2 mousePosition;
	Vector2 pMousePosition;
};


#endif
