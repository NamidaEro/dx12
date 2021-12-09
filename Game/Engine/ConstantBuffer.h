#pragma once

class ConstantBuffer
{
public:
	ConstantBuffer();
	~ConstantBuffer();

	void Init(const uint32& size, const uint32& count);

	void Clear();
	void PushData(const int32& rootParamIndex, const void* buffer, const uint32& size);

	D3D12_GPU_VIRTUAL_ADDRESS GetGpuVirtualAddress(const uint32& index);

private:
	void CreateBuffer();

private:
	ComPtr<ID3D12Resource> _cbvBuffer;
	BYTE* _mappedBuffer = nullptr;
	uint32 _elementSize = 0;
	uint32 _elementCount = 0;
	uint32 _currentIndex = 0;
};
