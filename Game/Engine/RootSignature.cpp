#include "pch.h"
#include "RootSignature.h"

#include "Device.h"
#include "Engine.h"

void RootSignature::Init()
{
	CD3DX12_ROOT_PARAMETER param[2];
	param[0].InitAsConstantBufferView(0);
	param[1].InitAsConstantBufferView(1);


	D3D12_ROOT_SIGNATURE_DESC desc = CD3DX12_ROOT_SIGNATURE_DESC(2, param);
	desc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

	ComPtr<ID3DBlob> blobSignature;
	ComPtr<ID3DBlob> blobError;

	::D3D12SerializeRootSignature(&desc, D3D_ROOT_SIGNATURE_VERSION_1, &blobSignature, &blobError);
	DEVICE->GetDevice()->CreateRootSignature(0
		, blobSignature->GetBufferPointer()
		, blobSignature->GetBufferSize()
		, IID_PPV_ARGS(&_signature));
}
