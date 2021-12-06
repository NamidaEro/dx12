#pragma once

class SwapChain;
class DescriptorHeap;
class CommandQueue
{
public:
	void Init(ComPtr<ID3D12Device> device
		, shared_ptr<SwapChain> swapChain);
	void WaitSync();

	void RenderBegin(const D3D12_VIEWPORT* vp, const D3D12_RECT* rect);
	void RenderEnd();

	const ComPtr<ID3D12CommandQueue> GetCmdQueue() { return _cmdQueue; }
	const ComPtr<ID3D12GraphicsCommandList>	GetCmdList() { return _cmdList; }

	~CommandQueue();

private:
	ComPtr<ID3D12CommandQueue>			_cmdQueue;
	ComPtr<ID3D12CommandAllocator>		_cmdAlloc;
	ComPtr<ID3D12GraphicsCommandList>	_cmdList;

	ComPtr<ID3D12Fence>					_fence;
	uint32								_fenceValue = 0;
	HANDLE								_fenceEvent = INVALID_HANDLE_VALUE;

	shared_ptr<SwapChain>				_swapChain;
	shared_ptr<DescriptorHeap>			_descHeap;

	ComPtr<ID3D12Device>				_device;
};

