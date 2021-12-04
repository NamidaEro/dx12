#include "pch.h"
#include "Engine.h"

void Engine::Init(const WindoInfo& window)
{
	_window = window;
}

void Engine::Render()
{
	int a = 0;
}

void Engine::ResizeWindow(int32 width, int32 height)
{
	_window.width = width;
	_window.height = height;

	RECT rect = { 0, 0, width, height };
	::AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
	::SetWindowPos(_window.hwnd, 0, 100, 100, width, height, 0);
}
