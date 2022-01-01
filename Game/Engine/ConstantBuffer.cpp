#include "pch.h"
#include "ConstantBuffer.h"

#include "CommandQueue.h"
#include "Device.h"
#include "Engine.h"
#include "TableDescriptorHeap.h"

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
		}

		_cbvBuffer = nullptr;
	}
}

void ConstantBuffer::Init(const CBV_REGISTER& reg, const uint32& size, const uint32& count)
{
	_reg = reg;

	_elementSize = (size + 255) & ~255;
	_elementCount = count;

	CreateBuffer();
	CreateView();
}

void ConstantBuffer::Clear()
{
	_currentIndex = 0;
}

void ConstantBuffer::PushData(const void* buffer, const uint32& size)
{
#ifdef _DEBUG
	assert(_currentIndex < _elementSize);
	assert(_elementSize == ((size + 255) & ~255));
#endif

	::memcpy(&_mappedBuffer[_currentIndex * _elementSize], buffer, size);

	const D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle = GetCpuHandle(_currentIndex);
	TABLEDESCHEAP->SetCBV(cpuHandle, _reg);

	_currentIndex++;
}

void ConstantBuffer::SetGlobalData(const void* buffer, const uint32& size)
{
#ifdef _DEBUG
	assert(_elementSize == ((size + 255) & ~255));
#endif
	::memcpy(&_mappedBuffer[0], buffer, size);

	CMDQUEUE->GetCmdList()->SetGraphicsRootConstantBufferView(0, GetGpuVirtualAddress(0));
}

D3D12_GPU_VIRTUAL_ADDRESS ConstantBuffer::GetGpuVirtualAddress(const uint32& index) const
{
	D3D12_GPU_VIRTUAL_ADDRESS objCBAddress = _cbvBuffer->GetGPUVirtualAddress();
	objCBAddress += (index * _elementSize);

	return objCBAddress;
}

D3D12_CPU_DESCRIPTOR_HANDLE ConstantBuffer::GetCpuHandle(const uint32& index)
{
	return CD3DX12_CPU_DESCRIPTOR_HANDLE(_cpuHandleBegin, index * _handleIncrementSize);
}


void ConstantBuffer::CreateBuffer()
{
	const uint32 bufferSize = _elementSize * _elementCount;
	const D3D12_HEAP_PROPERTIES heapProperty = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	const D3D12_RESOURCE_DESC desc = CD3DX12_RESOURCE_DESC::Buffer(bufferSize);

	DEVICE->GetDevice()->CreateCommittedResource(
		&heapProperty,
		D3D12_HEAP_FLAG_NONE,
		&desc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&_cbvBuffer));

	_cbvBuffer->Map(0, nullptr, reinterpret_cast<void**>(&_mappedBuffer));
}

void ConstantBuffer::CreateView()
{
	D3D12_DESCRIPTOR_HEAP_DESC desc = {};
	desc.NumDescriptors = _elementCount;
	desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	DEVICE->GetDevice()->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&_cbvHeap));

	_cpuHandleBegin = _cbvHeap->GetCPUDescriptorHandleForHeapStart();
	_handleIncrementSize = DEVICE->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	for(uint32 i = 0; i <_elementCount; ++i)
	{
		const D3D12_CPU_DESCRIPTOR_HANDLE handle = GetCpuHandle(i);

		D3D12_CONSTANT_BUFFER_VIEW_DESC cdesc = {};
		cdesc.BufferLocation = _cbvBuffer->GetGPUVirtualAddress() + static_cast<uint64>(_elementSize) * i;
		cdesc.SizeInBytes = _elementSize;

		DEVICE->GetDevice()->CreateConstantBufferView(&cdesc, handle);
	}
}
