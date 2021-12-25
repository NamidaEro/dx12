#include "pch.h"
#include "EnginePch.h"

#include "Engine.h"
#include "SceneManager.h"
#include "Input.h"
#include "Timer.h"

unique_ptr<Engine> g_engine = make_unique<Engine>();
unique_ptr<SceneManager> g_sceneManager = make_unique<SceneManager>();
unique_ptr<Input> g_input = make_unique<Input>();
unique_ptr<Timer> g_timer = make_unique<Timer>();

Engine& GEngine()
{
    return *(g_engine.get());
}

SceneManager& GSceneManager()
{
    return *(g_sceneManager.get());
}

Input& GInput()
{
    return *(g_input.get());
}

Timer& GTimer()
{
    return *(g_timer.get());
}
