#pragma once

class Device;
class CommandQueue;
class SwapChain;
class RootSignature;
class EXPORTCLASS Engine : public Singleton<Engine>
{
public:
	void Awake();
	void Init(const WindowInfo& window);
	void Render();

public:
	const shared_ptr<Device>				GetDeivce() { return _device; }
	const shared_ptr<CommandQueue>			GetCommandQueue() { return _cmdQueue; }
	const shared_ptr<SwapChain>				GetSwapChain() { return _swapChain;	}
	const shared_ptr<RootSignature>			GetSignature() { return _rootSignature; }

public:
	void RenderBegin();
	void RenderEnd();

	void ResizeWindow(int32 width, int32 height);

private:
	WindowInfo								_window;
	D3D12_VIEWPORT							_viewport = {};
	D3D12_RECT								_scissorRect = {};

	shared_ptr<Device>						_device;
	shared_ptr<CommandQueue>				_cmdQueue;
	shared_ptr<SwapChain>					_swapChain;
	shared_ptr<RootSignature>				_rootSignature;
};

