#include "pch.h"
#include "Engine.h"

#include "CommandQueue.h"
#include "Device.h"
#include "SwapChain.h"
#include "RootSignature.h"
#include "ConstantBuffer.h"

void Engine::Awake()
{
	_device = make_shared<Device>();
	_cmdQueue = make_shared<CommandQueue>();
	_swapChain = make_shared<SwapChain>();
	_rootSignature = make_shared<RootSignature>();
	_cb = make_shared<ConstantBuffer>();
}

void Engine::Init(const WindowInfo& window)
{
	_window = window;

	ResizeWindow(_window.width, _window.height);

	_viewport =
	{
		0, 0,
		static_cast<FLOAT>(_window.width), static_cast<FLOAT>(_window.height)
	};

	_scissorRect = CD3DX12_RECT(0, 0, _window.width, _window.height);	

	Instance().GetDeivce()->Init();
	Instance().GetCommandQueue()->Init();
	Instance().GetSwapChain()->Init(_window);
	Instance().GetSignature()->Init();
	Instance().GetConstantBuffer()->Init(sizeof(Transform), 256);
}

void Engine::Render()
{
	RenderBegin();

	RenderEnd();
}

void Engine::RenderBegin()
{
	Instance().GetCommandQueue()->RenderBegin(&_viewport, &_scissorRect);
}

void Engine::RenderEnd()
{
	Instance().GetCommandQueue()->RenderEnd();
}

void Engine::ResizeWindow(int32 width, int32 height)
{
	_window.width = width;
	_window.height = height;

	RECT rect = { 0, 0, width, height };
	::AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
	::SetWindowPos(_window.hwnd, 0, 100, 100, width, height, 0);
}
