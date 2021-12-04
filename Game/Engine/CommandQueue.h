#pragma once

class CommandQueue
{
public:

private:
	ComPtr<ID3D12CommandQueue> _cmdQueue;
	ComPtr<ID3D12CommandAllocator> _comAlloc;
	ComPtr<ID3D12GraphicsCommandList> _cmdList;

	ComPtr<ID3D12Fence> _fence;
	uint32 _fenceValue = 0;
	HANDLE _fenceEvent = INVALID_HANDLE_VALUE;

	shared_ptr<SwapChain> _swapChain;
	shared_ptr<DescriptorHeap> _descHeap;
};

