#pragma once
#include "Object.h"

class EXPORTCLASS Shader : public Object
{
public:
	Shader();
	virtual ~Shader();

public:
	void Init(const wstring& path);
	void Update();

private:
	void CreateShader(const wstring& path, const string& name, const string& version, ComPtr<ID3DBlob>& blob, D3D12_SHADER_BYTECODE& shaderByteCode);
	void CreateVertexShader(const wstring& path, const string& name, const string& version);
	void CreatePixelShader(const wstring& path, const string& name, const string& version);

private:
	ComPtr<ID3DBlob>						_vsBlob = nullptr;
	ComPtr<ID3DBlob>						_psBlob = nullptr;
	ComPtr<ID3DBlob>						_errBlob = nullptr;

	ComPtr<ID3D12PipelineState>				_pipelineState = nullptr;
	D3D12_GRAPHICS_PIPELINE_STATE_DESC		_pipelineDesc = {};
};

