#include "pch.h"
#include "SwapChain.h"

#include "CommandQueue.h"
#include "Device.h"
#include "Engine.h"

void SwapChain::Init(const WindowInfo& window)
{
	CreateSwapChain(window, DEVICE->GetDXGI(), CMDQUEUE->GetCmdQueue());

	CreateRTV(DEVICE->GetDevice());
}

void SwapChain::Present()
{
	_swapChain->Present(0, 0);
}

void SwapChain::SwapIndex()
{
	_backBufferIndex = (_backBufferIndex + 1) % SWAP_CHAIN_BUFFER_COUNT;
}


void SwapChain::CreateSwapChain(const WindowInfo& window, ComPtr<IDXGIFactory> dxgi,
	ComPtr<ID3D12CommandQueue> cmdQueue)
{
	_swapChain.Reset();

	DXGI_SWAP_CHAIN_DESC sd;
	sd.BufferDesc.Width = static_cast<uint32>(window.width);
	sd.BufferDesc.Height = static_cast<uint32>(window.height);
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = SWAP_CHAIN_BUFFER_COUNT;
	sd.OutputWindow = window.hwnd;
	sd.Windowed = window.isWindow;
	sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	dxgi->CreateSwapChain(cmdQueue.Get(), &sd, &_swapChain);

	for (int32 i = 0; i < SWAP_CHAIN_BUFFER_COUNT; ++i)
	{
		_swapChain->GetBuffer(i, IID_PPV_ARGS(&_rtvBuffer[i]));
	}
}

void SwapChain::CreateRTV(ComPtr<ID3D12Device> device)
{
	int32 rtvHeapSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	D3D12_DESCRIPTOR_HEAP_DESC desc;
	desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	desc.NumDescriptors = SWAP_CHAIN_BUFFER_COUNT;
	desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	desc.NodeMask = 0;

	device->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&_rtvHeap));

	D3D12_CPU_DESCRIPTOR_HANDLE heapBeigin = _rtvHeap->GetCPUDescriptorHandleForHeapStart();

	for (int i = 0; i < SWAP_CHAIN_BUFFER_COUNT; ++i)
	{
		_rtvHandle[i] = CD3DX12_CPU_DESCRIPTOR_HANDLE(heapBeigin, i * rtvHeapSize);
		device->CreateRenderTargetView(_rtvBuffer[i].Get(), nullptr, _rtvHandle[i]);
	}
}
