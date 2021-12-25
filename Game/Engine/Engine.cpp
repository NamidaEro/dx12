#include "pch.h"
#include "Engine.h"

#include "Timer.h"
#include "Input.h"

#include "Material.h"
#include "Transform.h"

#include "SceneManager.h"

Engine::Engine()
    : _device(make_shared<Device>()),
    _cmdQueue(make_shared<CommandQueue>()),
	_swapChain(make_shared<SwapChain>()),
	_rootSignature(make_shared<RootSignature>()),
	//_cb(make_shared<ConstantBuffer>()),
	_tableDescHealp(make_shared<TableDescriptorHeap>()),
	_depthStencilBuffer(make_shared<DepthStencilBuffer>())
{

}

void Engine::Awake()
{

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
	//_cb->Init(sizeof(MatrixTransform), 256);
	_tableDescHealp->Init(256);
	_depthStencilBuffer->Init(_window);
	GInput().Init(::GetActiveWindow());
	GTimer().Init();

	CreateConstantBuffer(CBV_REGISTER::b0, sizeof(MatrixTransform), 256);
	CreateConstantBuffer(CBV_REGISTER::b1, sizeof(MaterialParams), 256);

	ResizeWindow(_window.width, _window.height);
}

void Engine::Render()
{
	RenderBegin();

	GSceneManager().Update();

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

void Engine::Update()
{
	GInput().Update();
	GTimer().Update();

	Render();

	ShowFPS();
}

void Engine::ShowFPS()
{
	uint32 fps = GTimer().GetFps();

	WCHAR tex[100] = L"";
	::wsprintf(tex, L"FPS: %d", fps);

	::SetWindowText(_window.hwnd, tex);
}

void Engine::CreateConstantBuffer(const CBV_REGISTER& reg, const uint32& bufferSize, const uint32& count)
{
	uint8 typeInt = static_cast<uint8>(reg);

	shared_ptr<ConstantBuffer> buffer = make_shared<ConstantBuffer>();
	buffer->Init(reg, bufferSize, count);
	_constantBuffers.push_back(buffer);
}
