
#include "Game.h"
#include "Cube.h"
#include "Sphere.h"
#include <memory>

#include<iostream>
#include<string>

Game::Game()
	:
	wnd(800, 600, "Final Push")
{
	//init cubes
	for (auto i = 0; i < 4; i++)
	{
		cubes.push_back(std::make_unique<Cube>(
			wnd.Render(), i * 5, 5.0f, 15.0f));

	}
	for (auto i = 0; i < 1; i++)
	{
		spheres.push_back(std::make_unique<Sphere>(
			wnd.Render(), 0.0f, 5.0f, 0.0f, 3.0f, 20.0f, 20.0f));
	}

	wnd.Render().SetCamera(DirectX::XMMatrixTranslation(0.0f, 0.0f, 20.0f));

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
		Inputs();
		Update();
		Render();
	}
}

void Game::Inputs()
{
	auto Player = spheres.at(0).get();
	std::string debugW = "W\n";
	std::string debugA = "A\n";
	std::string debugS = "S\n";
	std::string debugD = "D\n";
	if (wnd.keyboard.KeyIsPressed('W'))
	{
		Player->setTransformXYZ(Player->getTransformXYZ().x, Player->getTransformXYZ().y + .1F, 0);

		OutputDebugString(debugW.c_str());
	}
	if (wnd.keyboard.KeyIsPressed('A'))
	{
		Player->setTransformXYZ(Player->getTransformXYZ().x - .1F, Player->getTransformXYZ().y, 0);
		OutputDebugString(debugA.c_str());
		cubes[1].get();
	}
	if (wnd.keyboard.KeyIsPressed('S'))
	{
		Player->setTransformXYZ(Player->getTransformXYZ().x, Player->getTransformXYZ().y - .1F, 0);
		OutputDebugString(debugS.c_str());
	}
	if (wnd.keyboard.KeyIsPressed('D'))
	{
		Player->setTransformXYZ(Player->getTransformXYZ().x + .1F, Player->getTransformXYZ().y, 0);
		OutputDebugString(debugD.c_str());
	}
}

void Game::Update()
{
	auto dt = time.Mark();

	for (auto& c : cubes)
	{
		c->Update(dt);
	}
	for (auto& s : spheres)
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