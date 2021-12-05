#include "pch.h"
#include "DescriptorHeap.h"

#include "SwapChain.h"

void DescriptorHeap::Init(ComPtr<ID3D12Device> device, shared_ptr<SwapChain> swapChain)
{
	_swapChain = swapChain;

	_rtvHeapSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	D3D12_DESCRIPTOR_HEAP_DESC desc;
	desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	desc.NumDescriptors = SWAP_CHAIN_BUFFER_COUNT;
	desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	desc.NodeMask = 0;

	device->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&_rtvHeap));

	D3D12_CPU_DESCRIPTOR_HANDLE heapBeigin = _rtvHeap->GetCPUDescriptorHandleForHeapStart();

	for(int i = 0; i <SWAP_CHAIN_BUFFER_COUNT; ++i)
	{
		_rtvHandle[i] = CD3DX12_CPU_DESCRIPTOR_HANDLE(heapBeigin, i * _rtvHeapSize);
		auto a = swapChain->GetRenderTarget(i).Get();
		device->CreateRenderTargetView(a, nullptr, _rtvHandle[i]);
	}
}

D3D12_CPU_DESCRIPTOR_HANDLE DescriptorHeap::GetBackBufferView()
{
	return GetRTV(_swapChain->GetCurrentBackBufferIndex());
}
