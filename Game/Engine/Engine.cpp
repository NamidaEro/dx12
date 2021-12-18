#include "pch.h"
#include "Engine.h"

#include <iostream>

#include "CommandQueue.h"
#include "Device.h"
#include "SwapChain.h"
#include "RootSignature.h"
#include "ConstantBuffer.h"
#include "TableDescriptorHeap.h"
#include "DepthStencilBuffer.h"

Engine::Engine()
    : _device(make_shared<Device>()),
    _cmdQueue(make_shared<CommandQueue>()),
	_swapChain(make_shared<SwapChain>()),
	_rootSignature(make_shared<RootSignature>()),
	_cb(make_shared<ConstantBuffer>()),
	_tableDescHealp(make_shared<TableDescriptorHeap>()),
	_depthStencilBuffer(make_shared<DepthStencilBuffer>())
{

}

void Engine::Awake()
{
	/*_device = make_shared<Device>();
	_cmdQueue = make_shared<CommandQueue>();
	_swapChain = make_shared<SwapChain>();
	_rootSignature = make_shared<RootSignature>();
	_cb = make_shared<ConstantBuffer>();
	_tableDescHealp = make_shared<TableDescriptorHeap>();
	_depthStencilBuffer = make_shared<DepthStencilBuffer>();*/
}

void Engine::Init(const WindowInfo& window)
{
	_window = window;

	_viewport =
	{
		0, 0,
		static_cast<FLOAT>(_window.width), static_cast<FLOAT>(_window.height)
	};

	_scissorRect = CD3DX12_RECT(0, 0, _window.width, _window.height);

	_device->Init();
	_cmdQueue->Init();
	_swapChain->Init(_window);
	_rootSignature->Init();
	_cb->Init(sizeof(Transform), 256);
	_tableDescHealp->Init(256);
	_depthStencilBuffer->Init(_window);

	ResizeWindow(_window.width, _window.height);
}

void Engine::Render()
{
	RenderBegin();

	RenderEnd();
}

void Engine::RenderBegin() const
{
	_cmdQueue->RenderBegin(&_viewport, &_scissorRect);
}

void Engine::RenderEnd()
{
	_cmdQueue->RenderEnd();
}

void Engine::ResizeWindow(const int32& width, const int32& height)
{
	_window.width = width;
	_window.height = height;

	RECT rect = { 0, 0, width, height };
	::AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
	::SetWindowPos(_window.hwnd, 0, 100, 100, width, height, 0);

	_depthStencilBuffer->Init(_window);
}
