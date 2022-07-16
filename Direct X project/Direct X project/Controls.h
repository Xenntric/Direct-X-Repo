#pragma once
#include "Keyboard.h"

class Controls
{
	void keyboarddoer();
private:
	Keyboard keyboard;
	Keyboard::Event keyboardEvent;
};

