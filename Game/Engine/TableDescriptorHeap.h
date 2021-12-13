#pragma once

class TableDescriptorHeap
{
public:
	void Init(const uint32& count);

	void Clear();
	void SetCBV(const D3D12_CPU_DESCRIPTOR_HANDLE& handle, const CBV_REGISTER& reg) const;
	void SetSRV(const D3D12_CPU_DESCRIPTOR_HANDLE& handle, const SRV_REGISTER& reg) const;
	void CommitTable();

	ComPtr<ID3D12DescriptorHeap> GetDescriptorHeap() const { return _descHeap; }

	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUHandle(const CBV_REGISTER& reg) const;
	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUHandle(const SRV_REGISTER& reg) const;

private:
	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUHandle(const uint8& reg) const;

private:
	ComPtr<ID3D12DescriptorHeap>	_descHeap = nullptr;
	uint64							_handleSize = 0;
	uint64							_groupSize = 0;
	uint64							_grouCount = 0;

	uint32							_currentGroupIndex = 0;
};

