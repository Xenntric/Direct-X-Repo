#pragma once
#include "Window.h"
#include "GameTimer.h"
#include "KeyboardClass.h"
class Game
{
public:
	Game();
	// master frame / message loop
	int init();
	~Game();
private:
	void Update();
	void Render();
	void Inputs();

private:
	Window wnd;
	GameTimer time;
	
	std::vector<std::unique_ptr<class Cube>> cubes;
	std::vector<std::unique_ptr<class Sphere>> spheres;
};