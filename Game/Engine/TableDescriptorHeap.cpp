#include "pch.h"
#include "TableDescriptorHeap.h"

#include "Device.h"
#include "Engine.h"
#include "CommandQueue.h"

void TableDescriptorHeap::Init(const uint32& count)
{
	_grouCount = count;

	D3D12_DESCRIPTOR_HEAP_DESC desc = {};
	desc.NumDescriptors = count * (REGISTER_COUNT - 1);
	desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;

	DEVICE->GetDevice()->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&_descHeap));

	_handleSize = DEVICE->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	_groupSize = _handleSize * (REGISTER_COUNT - 1);
}

void TableDescriptorHeap::Clear()
{
	_currentGroupIndex = 0;
}

void TableDescriptorHeap::SetCBV(const D3D12_CPU_DESCRIPTOR_HANDLE& handle, const CBV_REGISTER& reg) const
{
	const D3D12_CPU_DESCRIPTOR_HANDLE destHandle = GetCPUHandle(reg);

	constexpr uint32 destRange = 1;
	constexpr uint32 srcRange = 1;
	DEVICE->GetDevice()->CopyDescriptors(
		1, &destHandle, &destRange,
		1, &handle, &srcRange,
		D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
}

void TableDescriptorHeap::SetSRV(const D3D12_CPU_DESCRIPTOR_HANDLE& handle, const SRV_REGISTER& reg) const
{
	const D3D12_CPU_DESCRIPTOR_HANDLE destHandle = GetCPUHandle(reg);

	constexpr uint32 destRange = 1;
	constexpr uint32 srcRange = 1;
	DEVICE->GetDevice()->CopyDescriptors(
		1, &destHandle, &destRange,
		1, &handle, &srcRange,
		D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
}

void TableDescriptorHeap::CommitTable()
{
	D3D12_GPU_DESCRIPTOR_HANDLE handle = _descHeap->GetGPUDescriptorHandleForHeapStart();
	handle.ptr += _currentGroupIndex * _groupSize;
	CMDQUEUE->GetCmdList()->SetGraphicsRootDescriptorTable(1, handle);

	_currentGroupIndex++;
}

D3D12_CPU_DESCRIPTOR_HANDLE TableDescriptorHeap::GetCPUHandle(const CBV_REGISTER& reg) const
{
	return GetCPUHandle(static_cast<uint8>(reg));
}

D3D12_CPU_DESCRIPTOR_HANDLE TableDescriptorHeap::GetCPUHandle(const SRV_REGISTER& reg) const
{
	return GetCPUHandle(static_cast<uint8>(reg));
}

D3D12_CPU_DESCRIPTOR_HANDLE TableDescriptorHeap::GetCPUHandle(const uint8& reg) const
{
	assert(0 < reg);
	D3D12_CPU_DESCRIPTOR_HANDLE handle = _descHeap->GetCPUDescriptorHandleForHeapStart();
	handle.ptr += _currentGroupIndex * _groupSize;
	handle.ptr += (reg - 1) * _handleSize;

	return handle;
}
