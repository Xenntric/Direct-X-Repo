#pragma once
#include "Window.h"
#include "GameTimer.h"
#include "Keyboard.h"

class Game
{
public:
	Game();
	// master frame / message loop
	int init();
	~Game();
private:
	void Inputs();
	void Update();
	void Render();

private:
	Window wnd;
	GameTimer time;
	Keyboard keyboard;
	std::vector<std::unique_ptr<class Cube>> cubes;
	std::vector<std::unique_ptr<class Sphere>> spheres;
};