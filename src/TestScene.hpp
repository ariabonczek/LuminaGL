#ifndef TESTSCENE_HPP
#define TESTSCENE_HPP

#include "Config.hpp"
#include "Scene.hpp"

class TestScene : public LuminaGL::Scene
{
public:
	TestScene();
	~TestScene();

	void LoadAssets();
	void Update(float dt);
	void Draw();
private:

};


#endif
