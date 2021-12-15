#pragma once

class EXPORTCLASS SwapChain
{
public:
	void Init(const WindowInfo& window);
	void Present();
	void SwapIndex();

	ComPtr<IDXGISwapChain> GetSwapChain() const { return _swapChain; }
	ComPtr<ID3D12Resource> GetRenderTarget(const int32& index) const  { return _rtvBuffer[index]; }
	
	ComPtr<ID3D12Resource> GetBackRTVBuffer() const { return _rtvBuffer[_backBufferIndex]; }
	D3D12_CPU_DESCRIPTOR_HANDLE GetBackRTV() const { return _rtvHandle[_backBufferIndex]; }

private:
	void CreateSwapChain(const WindowInfo& window, ComPtr<IDXGIFactory> dxgi, ComPtr<ID3D12CommandQueue> cmdQueue);
	void CreateRTV(ComPtr<ID3D12Device> device);

private:
	ComPtr<IDXGISwapChain>			_swapChain = nullptr;

	ComPtr<ID3D12Resource>			_rtvBuffer[SWAP_CHAIN_BUFFER_COUNT];
	ComPtr<ID3D12DescriptorHeap>	_rtvHeap;
	D3D12_CPU_DESCRIPTOR_HANDLE		_rtvHandle[SWAP_CHAIN_BUFFER_COUNT];

	uint32							_backBufferIndex = 0;
};

