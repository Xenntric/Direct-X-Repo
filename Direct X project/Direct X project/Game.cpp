
#include "Game.h"
#include "Cube.h"
#include "Sphere.h"
#include <memory>

Game::Game()
	:
	wnd(800, 600, "Factory Pattern Refactor!! :D")
{
	//init cubes
	/*for (auto i = 0; i < 4; i++)
	{
		cubes.push_back(std::make_unique<Cube>(
			wnd.Render(), i*5, 5.0f, 15.0f));
		
	}*/
	for (auto i = 0; i < 1; i++)
	{
		spheres.push_back(std::make_unique<Sphere>(
			wnd.Render(),0.0f, 5.0f, 15.0f, 3.0f, 20.0f, 20.0f));
	}
	wnd.Render().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f));
}

int Game::init()
{
	while (true)
	{
		if (const auto ecode = Window::ProcessMessages())
		{
			return *ecode;
		}
		Update();
		Render();
	}
}

void Game::Update()
{
	auto dt = time.Mark();

	for (auto& c : cubes)
	{
		c->Update(dt);
	}
	for (auto& s : cubes)
	{
		s->Update(dt);
	}

}

void Game::Render()
{
	const float c = sin(time.Peek()) / 2.0f + 0.5f;

	wnd.Render().ClearBuffer(c, 1.0f, 1.0f);
	
	for (auto& c : cubes)
	{
		c->Draw(wnd.Render());
	}
	for (auto& s : spheres)
	{
		s->Draw(wnd.Render());
	}

	wnd.Render().EndFrame();
}
Game::~Game()
{
}