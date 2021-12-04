#pragma once

#include "../Utils/Macros.h"

class __declspec(dllexport) Engine
{
public:
	void Init(const WindoInfo& window);
	void Render();

	void ResizeWindow(int32 width, int32 height);

private:
	WindoInfo		_window;
	D3D12_VIEWPORT	_viewport = {};
	D3D12_RECT		_scissorRect = {};
};

