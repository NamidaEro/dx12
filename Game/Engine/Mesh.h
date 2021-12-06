#pragma once

class EXPORTCLASS Mesh
{
public:
	void Init(ComPtr<ID3D12Device> device
		, ComPtr<ID3D12GraphicsCommandList> cmdList
		, vector<Vertex>& vec);
	void Render();

private:
	ComPtr<ID3D12Resource> _vertexBuffer = nullptr;
	D3D12_VERTEX_BUFFER_VIEW _vertexBufferView = {};

	uint32 _vertexCount = 0;

	ComPtr<ID3D12Device> _device = nullptr;
	ComPtr<ID3D12GraphicsCommandList> _cmdList = nullptr;
};

