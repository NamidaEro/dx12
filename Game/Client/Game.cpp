#include "pch.h"
#include "Game.h"

void Game::Init(const WindowInfo& window)
{
	if(_engine == nullptr)
	{
		_engine = make_unique<Engine>();
	}
	
	_engine->Init(window);
}

void Game::Update()
{
	_engine->Render();
}
