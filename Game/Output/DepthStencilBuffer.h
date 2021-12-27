#pragma once

class EXPORTCLASS DepthStencilBuffer
{
public:
	void Init(const WindowInfo& window, const DXGI_FORMAT& dsvFormat = DXGI_FORMAT_D32_FLOAT);

	D3D12_CPU_DESCRIPTOR_HANDLE GetDSVCpuHandle() const { return _dsvHandle; }
	DXGI_FORMAT GetDSVFormat() const { return _dsvFormat; }

private:
	ComPtr<ID3D12Resource>			_dsvBuffer = nullptr;
	ComPtr<ID3D12DescriptorHeap>	_dsvHeap = nullptr;
	D3D12_CPU_DESCRIPTOR_HANDLE		_dsvHandle = {};
	DXGI_FORMAT						_dsvFormat = {};
};

