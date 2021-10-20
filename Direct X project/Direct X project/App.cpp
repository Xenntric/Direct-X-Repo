
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
	wnd.Render().ClearBuffer(c, c, 1.0f);

	wnd.Render().DrawTestTriangle();

	wnd.Render().EndFrame();

	/*const float t = time.Peek();
	std::ostringstream oss;
	oss << "Time Elapsed: " << std::setprecision(1) << std::fixed << t << "sec";*/
}