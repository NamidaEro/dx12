#pragma once

class EXPORTCLASS Mesh
{
public:
	void Init(vector<Vertex>& vec);
	void Render();

private:
	ComPtr<ID3D12Resource> _vertexBuffer = nullptr;
	D3D12_VERTEX_BUFFER_VIEW _vertexBufferView = {};

	uint32 _vertexCount = 0;
};

