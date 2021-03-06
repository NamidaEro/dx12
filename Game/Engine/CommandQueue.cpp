#include "pch.h"
#include "CommandQueue.h"

#include <iostream>

#include "ConstantBuffer.h"
#include "DepthStencilBuffer.h"
#include "Device.h"
#include "Engine.h"
#include "RootSignature.h"
#include "SwapChain.h"
#include "TableDescriptorHeap.h"

void CommandQueue::Init()
{
	const auto device = DEVICE->GetDevice();

	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;

	device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&_cmdQueue));
	device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&_cmdAlloc));
	device->CreateCommandList(
		0
		, D3D12_COMMAND_LIST_TYPE_DIRECT
		, _cmdAlloc.Get()
		, nullptr
		, IID_PPV_ARGS(&_cmdList)
	);
	_cmdList->Close();
	
	device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&_resCmdAlloc));
	device->CreateCommandList(
		0
		, D3D12_COMMAND_LIST_TYPE_DIRECT
		, _resCmdAlloc.Get()
		, nullptr
		, IID_PPV_ARGS(&_resCmdList)
	);
	
	device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&_fence));
	_fenceEvent = ::CreateEvent(nullptr, FALSE, FALSE, nullptr);
}

void CommandQueue::WaitSync()
{
	_fenceValue++;

	_cmdQueue->Signal(_fence.Get(), _fenceValue);

	if(_fence->GetCompletedValue() < _fenceValue)
	{
		_fence->SetEventOnCompletion(_fenceValue, _fenceEvent);

		::WaitForSingleObject(_fenceEvent, INFINITE);
	}
}

void CommandQueue::RenderBegin(const D3D12_VIEWPORT* vp, const D3D12_RECT* rect) const
{
	_cmdAlloc->Reset();
	_cmdList->Reset(_cmdAlloc.Get(), nullptr);

	const D3D12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
		SWAPCHAIN->GetBackRTVBuffer().Get(),
		D3D12_RESOURCE_STATE_PRESENT,
		D3D12_RESOURCE_STATE_RENDER_TARGET);

	_cmdList->SetGraphicsRootSignature(SIGNATURE->GetSignature().Get());

	CONSTANTBUFFER(CONSTANT_BUFFER_TYPE::TRANSFORM)->Clear();
	CONSTANTBUFFER(CONSTANT_BUFFER_TYPE::MATERIAL)->Clear();
	TABLEDESCHEAP->Clear();

	ID3D12DescriptorHeap* descHeap = TABLEDESCHEAP->GetDescriptorHeap().Get();
	_cmdList->SetDescriptorHeaps(1, &descHeap);

	_cmdList->ResourceBarrier(1, &barrier);

	_cmdList->RSSetViewports(1, vp);
	_cmdList->RSSetScissorRects(1, rect);

	const D3D12_CPU_DESCRIPTOR_HANDLE backBufferView = SWAPCHAIN->GetBackRTV();
	_cmdList->ClearRenderTargetView(backBufferView, Colors::Black, 0, nullptr);

	const D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = DSBUFFER->GetDSVCpuHandle();
	_cmdList->OMSetRenderTargets(1, &backBufferView, FALSE, &dsvHandle);
	_cmdList->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
}

void CommandQueue::RenderEnd()
{
	const D3D12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
		SWAPCHAIN->GetBackRTVBuffer().Get(),
		D3D12_RESOURCE_STATE_RENDER_TARGET,
		D3D12_RESOURCE_STATE_PRESENT);

	_cmdList->ResourceBarrier(1, &barrier);
	_cmdList->Close();

	ID3D12CommandList* cmdListArr[] = { _cmdList.Get() };
	_cmdQueue->ExecuteCommandLists(_countof(cmdListArr), cmdListArr);

	SWAPCHAIN->Present();

	WaitSync();

	SWAPCHAIN->SwapIndex();
}

void CommandQueue::FlushResourceCommandQueue()
{
	_resCmdList->Close();

	ID3D12CommandList* cmdListArr[] = { _resCmdList.Get() };
	_cmdQueue->ExecuteCommandLists(_countof(cmdListArr), cmdListArr);

	WaitSync();

	_resCmdAlloc->Reset();
	_resCmdList->Reset(_resCmdAlloc.Get(), nullptr);
}

CommandQueue::~CommandQueue()
{
	::CloseHandle(_fenceEvent);
}
