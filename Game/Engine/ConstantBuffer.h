#pragma once

class EXPORTCLASS ConstantBuffer
{
public:
	ConstantBuffer();
	~ConstantBuffer();

	void Init(const CBV_REGISTER& reg, const uint32& size, const uint32& count);

	void Clear();
	void PushData(const void* buffer, const uint32& size);

	void SetGlobalData(const void* buffer, const uint32& size);

	D3D12_GPU_VIRTUAL_ADDRESS GetGpuVirtualAddress(const uint32& index) const;
	D3D12_CPU_DESCRIPTOR_HANDLE GetCpuHandle(const uint32& index);

private:
	void CreateBuffer();
	void CreateView();

private:
	ComPtr<ID3D12Resource>			_cbvBuffer = nullptr;
	ComPtr<ID3D12DescriptorHeap>	_cbvHeap = nullptr;

	D3D12_CPU_DESCRIPTOR_HANDLE		_cpuHandleBegin = {};

	BYTE*							_mappedBuffer = nullptr;
	uint32							_elementSize = 0;
	uint32							_elementCount = 0;
	uint32							_currentIndex = 0;
	uint32							_handleIncrementSize = 0;

	CBV_REGISTER					_reg = {};
};
