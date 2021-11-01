
#include "App.h"

App::App()
	:
	wnd(800, 600, "Application Class Update")
{}

int App::init()
{
	while (true)
	{
		if (const auto ecode = Window::ProcessMessages())
		{
			return *ecode;
		}
		Update();
	}
}

void App::Update()
{
	const float c = sin(time.Peek()) / 2.0f + 0.5f;
	wnd.Render().ClearBuffer(c, 1.0f, 1.0f);

	wnd.Render().DrawTestTriangle(time.Peek()/2,
		0.0f,
		0.0f);

	wnd.Render().DrawTestTriangle(time.Peek(), 
		wnd.mouseX/800 - 1.0f, 
		-wnd.mouseY/600 + 1.0f);

	

	wnd.Render().EndFrame();

}