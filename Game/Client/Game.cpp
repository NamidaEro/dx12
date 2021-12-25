#include "pch.h"
#include "Game.h"

#include "SceneManager.h"
#include "GameObject.h"

shared_ptr<GameObject> gameObject = make_shared<GameObject>();

void Game::Init(const WindowInfo& window)
{
	GEngine().Init(window);

	GSceneManager().LoadScene(L"TestScene");
}

void Game::Update()
{
	GEngine().Update();
}
