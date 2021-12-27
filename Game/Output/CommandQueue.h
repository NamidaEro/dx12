#pragma once

class EXPORTCLASS CommandQueue
{
public:
	void Init();
	void WaitSync();

	void RenderBegin(const D3D12_VIEWPORT* vp, const D3D12_RECT* rect) const;
	void RenderEnd();

	void FlushResourceCommandQueue();

	ComPtr<ID3D12CommandQueue>			GetCmdQueue() const { return _cmdQueue; }
	ComPtr<ID3D12GraphicsCommandList>	GetCmdList() const { return _cmdList; }
	ComPtr<ID3D12GraphicsCommandList>	GetResCmdList() const { return _resCmdList; }

	~CommandQueue();

private:
	ComPtr<ID3D12CommandQueue>			_cmdQueue;
	ComPtr<ID3D12CommandAllocator>		_cmdAlloc;
	ComPtr<ID3D12GraphicsCommandList>	_cmdList;

	ComPtr<ID3D12CommandAllocator>		_resCmdAlloc;
	ComPtr<ID3D12GraphicsCommandList>	_resCmdList;

	ComPtr<ID3D12Fence>					_fence;
	uint32								_fenceValue = 0;
	HANDLE								_fenceEvent = INVALID_HANDLE_VALUE;
};

