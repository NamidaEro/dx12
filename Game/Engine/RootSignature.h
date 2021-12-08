#pragma once

class RootSignature
{
public:
	void Init();

	const ComPtr<ID3D12RootSignature> GetSignature() { return _signature; }

private:
	ComPtr<ID3D12RootSignature> _signature;
};

