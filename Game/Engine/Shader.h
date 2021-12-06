#pragma once

class EXPORTCLASS Shader
{
public:
	void Init(ComPtr<ID3D12Device> device
		, ComPtr<ID3D12GraphicsCommandList> cmdList
		, ComPtr<ID3D12RootSignature> signature
		, const wstring& path);
	void Update();

private:
	void CreateShader(const wstring& path, const string& name, const string& version, ComPtr<ID3DBlob>& blob, D3D12_SHADER_BYTECODE& shaderByteCode);
	void CreateVertexShader(const wstring& path, const string& name, const string& version);
	void CreatePixelShader(const wstring& path, const string& name, const string& version);

private:
	ComPtr<ID3DBlob> _vsBlob = nullptr;
	ComPtr<ID3DBlob> _psBlob = nullptr;
	ComPtr<ID3DBlob> _errBlob = nullptr;

	ComPtr<ID3D12PipelineState> _pipelineState = nullptr;
	D3D12_GRAPHICS_PIPELINE_STATE_DESC _pipelineDesc = {};

	ComPtr<ID3D12Device> _device = nullptr;
	ComPtr<ID3D12GraphicsCommandList> _cmdList = nullptr;
	ComPtr<ID3D12RootSignature> _signature = nullptr;
};

