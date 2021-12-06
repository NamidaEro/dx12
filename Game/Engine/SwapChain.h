#pragma once

class SwapChain
{
public:
	void Init(const WindowInfo& window
		, ComPtr<ID3D12Device> device
		, ComPtr<IDXGIFactory> dxgi
		, ComPtr<ID3D12CommandQueue> cmdQueue);
	void Present();
	void SwapIndex();

	const ComPtr<IDXGISwapChain> GetSwapChain() { return _swapChain; }
	const ComPtr<ID3D12Resource> GetRenderTarget(int32 index) { return _rtvBuffer[index]; }
	
	const ComPtr<ID3D12Resource> GetBackRTVBuffer() { return _rtvBuffer[_backBufferIndex]; }
	const D3D12_CPU_DESCRIPTOR_HANDLE GetBackRTV() { return _rtvHandle[_backBufferIndex]; }

private:
	void CreateSwapChain(const WindowInfo& window, ComPtr<IDXGIFactory> dxgi, ComPtr<ID3D12CommandQueue> cmdQueue);
	void CreateRTV(ComPtr<ID3D12Device> device);

private:
	ComPtr<IDXGISwapChain>			_swapChain = nullptr;

	ComPtr<ID3D12Resource>			_rtvBuffer[SWAP_CHAIN_BUFFER_COUNT];
	ComPtr<ID3D12DescriptorHeap>	_rtvHeap;
	D3D12_CPU_DESCRIPTOR_HANDLE		_rtvHandle[SWAP_CHAIN_BUFFER_COUNT];

	uint32							_backBufferIndex = 0;

	ComPtr<ID3D12Device>			_device = nullptr;
};

