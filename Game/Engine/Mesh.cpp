#include "pch.h"
#include "Mesh.h"

#include "CommandQueue.h"
#include "ConstantBuffer.h"
#include "Device.h"
#include "Engine.h"
#include "TableDescriptorHeap.h"

void Mesh::Init(vector<Vertex>& vec)
{
	_vertexCount = static_cast<uint32>(vec.size());
	const uint32 bufferSize = _vertexCount * sizeof(Vertex);

	const D3D12_HEAP_PROPERTIES heapProperty = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	const D3D12_RESOURCE_DESC desc = CD3DX12_RESOURCE_DESC::Buffer(bufferSize);

	DEVICE->GetDevice()->CreateCommittedResource(
		&heapProperty,
		D3D12_HEAP_FLAG_NONE,
		&desc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&_vertexBuffer)
	);

	void* vertexDataBuffer = nullptr;
	const CD3DX12_RANGE readRange(0, 0);
	_vertexBuffer->Map(0, &readRange, &vertexDataBuffer);
	::memcpy(vertexDataBuffer, &vec[0], bufferSize);
	_vertexBuffer->Unmap(0, nullptr);

	_vertexBufferView.BufferLocation = _vertexBuffer->GetGPUVirtualAddress();
	_vertexBufferView.StrideInBytes = sizeof(Vertex);
	_vertexBufferView.SizeInBytes = bufferSize;
}

void Mesh::Render() const
{
	CMDQUEUE->GetCmdList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	CMDQUEUE->GetCmdList()->IASetVertexBuffers(0, 1, &_vertexBufferView);

	{
		const auto handle = CONSTANTBUFFER->PushData(0, &_transform, sizeof(_transform));
		TABLEDESCHEAP->SetCBV(handle, CBV_REGISTER::b0);
	}

	{
		const auto handle = CONSTANTBUFFER->PushData(1, &_transform, sizeof(_transform));
		TABLEDESCHEAP->SetCBV(handle, CBV_REGISTER::b1);
	}

	TABLEDESCHEAP->CommitTable();

	//CMDQUEUE->GetCmdList()->SetGraphicsRootConstantBufferView(0, );

	CMDQUEUE->GetCmdList()->DrawInstanced(_vertexCount, 1, 0, 0);
}
