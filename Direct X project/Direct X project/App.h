#pragma once
#include "Window.h"
#include "AppTimer.h"
#include <optional>

class App
{
public:
	App();
	// master frame / message loop
	int init();

private:
	void Update();

private:
	Window wnd;
	AppTimer time;
};