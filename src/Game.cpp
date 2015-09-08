#include "Game.hpp"

NS_BEGIN

Game Game::instance;

Game::~Game()
{

}

Game* Game::GetInstance()
{
	return &instance;
}

int Game::Run()
{
	Initialize();

	// Game Loop
	while (!window.ShouldClose())
	{
		window.Clear();

		scene.Update(0.0167f);
		scene.Draw();

		window.Display();
	}

	Shutdown();

	return 1;
}

Game::Game()
{

}

bool Game::Initialize()
{
	if (!glfwInit())
		return false;

	window.Initialize(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

	glewExperimental = true;
	if (glewInit() != GLEW_OK)
		return false;

	return true;
}

bool Game::Shutdown()
{
	window.Shutdown();

	return true;
}



NS_END