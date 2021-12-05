#pragma once

#include "EnginePch.h"
#include "Engine.h"

class Game
{
public:
	void Init(const WindowInfo& window);
	void Update();

private:
	unique_ptr<Engine> _engine;
};

