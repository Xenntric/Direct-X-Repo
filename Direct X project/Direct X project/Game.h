#pragma once
#include "Window.h"
#include "GameTimer.h"

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

private:
	Window wnd;
	GameTimer time;
	std::vector<std::unique_ptr<class Cube>> cubes;
};