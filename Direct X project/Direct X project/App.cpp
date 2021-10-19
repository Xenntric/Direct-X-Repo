
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
	const float t = time.Peek();
	std::ostringstream oss;
	oss << "Time Elapsed: " << std::setprecision(1) << std::fixed << t << "sec";

}