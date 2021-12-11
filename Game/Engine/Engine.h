#pragma once

class Device;
class CommandQueue;
class SwapChain;
class RootSignature;
class ConstantBuffer;
class TableDescriptorHeap;
class EXPORTCLASS Engine : public Singleton<Engine>
{
public:
	void Awake();
	void Init(const WindowInfo& window);
	void Render();

public:
	shared_ptr<Device>					GetDeivce() const { return _device; }
	shared_ptr<CommandQueue>			GetCommandQueue() const { return _cmdQueue; }
	shared_ptr<SwapChain>				GetSwapChain() const { return _swapChain;	}
	shared_ptr<RootSignature>			GetSignature() const  { return _rootSignature; }
	shared_ptr<ConstantBuffer>			GetConstantBuffer() const { return _cb; }
	shared_ptr<TableDescriptorHeap>		GetTableDescHeap() const { return _tableDescHealp; }

public:
	void RenderBegin();
	void RenderEnd();

	void ResizeWindow(int32 width, int32 height);

private:
	WindowInfo								_window = {};
	D3D12_VIEWPORT							_viewport = {};
	D3D12_RECT								_scissorRect = {};

	shared_ptr<Device>						_device = nullptr;
	shared_ptr<CommandQueue>				_cmdQueue = nullptr;
	shared_ptr<SwapChain>					_swapChain = nullptr;
	shared_ptr<RootSignature>				_rootSignature = nullptr;
	shared_ptr<ConstantBuffer>				_cb = nullptr;
	shared_ptr<TableDescriptorHeap>			_tableDescHealp = nullptr;
};

