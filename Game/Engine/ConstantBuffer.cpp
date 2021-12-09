#include "pch.h"
#include "ConstantBuffer.h"

#include "CommandQueue.h"
#include "Device.h"
#include "Engine.h"

ConstantBuffer::ConstantBuffer()
{
}

ConstantBuffer::~ConstantBuffer()
{
	if(_cbvBuffer)
	{
		if(_cbvBuffer != nullptr)
		{
			_cbvBuffer->Unmap(0, nullptr);
			_cbvBuffer = nullptr;
		}
	}
}

void ConstantBuffer::Init(const uint32& size, const uint32& count)
{
	_elementSize = (size + 255) & ~255;
	_elementCount = count;

	CreateBuffer();
}

void ConstantBuffer::Clear()
{
	_currentIndex = 0;
}

void ConstantBuffer::PushData(const int32& rootParamIndex, const void* buffer, const uint32& size)
{
	assert(_currentIndex < _elementSize);

	::memcpy(&_mappedBuffer[_currentIndex * _elementSize], buffer, size);

	D3D12_GPU_VIRTUAL_ADDRESS address = GetGpuVirtualAddress(_currentIndex);
	CMDQUEUE->GetCmdList()->SetGraphicsRootConstantBufferView(rootParamIndex, address);
	_currentIndex++;
}

D3D12_GPU_VIRTUAL_ADDRESS ConstantBuffer::GetGpuVirtualAddress(const uint32& index)
{
	D3D12_GPU_VIRTUAL_ADDRESS objCBAddress = _cbvBuffer->GetGPUVirtualAddress();
	objCBAddress += (index * _elementSize);

	return objCBAddress;
}


void ConstantBuffer::CreateBuffer()
{
	uint32 bufferSize = _elementSize * _elementCount;
	D3D12_HEAP_PROPERTIES heapProperty = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	D3D12_RESOURCE_DESC desc = CD3DX12_RESOURCE_DESC::Buffer(bufferSize);

	DEVICE->GetDevice()->CreateCommittedResource(
		&heapProperty,
		D3D12_HEAP_FLAG_NONE,
		&desc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&_cbvBuffer));

	_cbvBuffer->Map(0, nullptr, reinterpret_cast<void**>(&_mappedBuffer));
}