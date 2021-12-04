#include "pch.h"
#include "EnginePch.h"

#include "../Engine/Engine.h"


unique_ptr<Engine> GEngine;

const Engine* GetEngine()
{
	return GEngine.get();
}
