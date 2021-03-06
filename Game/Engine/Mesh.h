#pragma once
#include "Object.h"

class Material;
class EXPORTCLASS Mesh : public Object
{
public:
	Mesh();
	virtual ~Mesh();

public:
	void Init(const vector<Vertex>& vertexBuffer, const vector<uint32>& indexbuffer);
	void Render() const;

private:
	void CreateVertexBuffer(const vector<Vertex>& buffer);
	void CreateIndexBuffer(const vector<uint32>& buffer);

private:
	ComPtr<ID3D12Resource>		_vertexBuffer = nullptr;
	D3D12_VERTEX_BUFFER_VIEW	_vertexBufferView = {};
	uint32						_vertexCount = 0;

	ComPtr<ID3D12Resource>		_indexBuffer = nullptr;
	D3D12_INDEX_BUFFER_VIEW		_indexBufferView = {};
	uint32						_indexCount = 0;
};

