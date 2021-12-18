#pragma once

class Device;
class CommandQueue;
class SwapChain;
class RootSignature;
class ConstantBuffer;
class TableDescriptorHeap;
class DepthStencilBuffer;
class EXPORTCLASS Engine
{
public:
	Engine();

public:
	void Awake();
	void Init(const WindowInfo& window);
	void Render();

public:
	void RenderBegin() const;
	void RenderEnd();

	void ResizeWindow(const int32& width, const int32& height);

public:
	shared_ptr<Device>								GetDeivce() { return _device; }
	shared_ptr<CommandQueue>						GetCommandQueue() { return _cmdQueue; }
	shared_ptr<SwapChain>							GetSwapChain() { return _swapChain; }
	shared_ptr<RootSignature>						GetSignature() { return _rootSignature; }
	shared_ptr<ConstantBuffer>						GetConstantBuffer() { return _cb; }
	shared_ptr<TableDescriptorHeap>					GetTableDescHeap() { return _tableDescHealp; }
	shared_ptr<DepthStencilBuffer>					GetDepthStencilBuffer() { return _depthStencilBuffer; }

private:
	WindowInfo										_window = {};
	D3D12_VIEWPORT									_viewport = {};
	D3D12_RECT										_scissorRect = {};

	shared_ptr<Device>								_device;
	shared_ptr<CommandQueue>						_cmdQueue;
	shared_ptr<SwapChain>							_swapChain;
	shared_ptr<RootSignature>						_rootSignature;
	shared_ptr<ConstantBuffer>						_cb;
	shared_ptr<TableDescriptorHeap>					_tableDescHealp;
	shared_ptr<DepthStencilBuffer>					_depthStencilBuffer;
};
