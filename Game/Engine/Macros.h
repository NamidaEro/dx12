#pragma once

#define ENGINE                      GEngine()
#define DEVICE				        ENGINE.GetDeivce()
#define SWAPCHAIN			        ENGINE.GetSwapChain()
#define SIGNATURE			        ENGINE.GetSignature()
#define CMDQUEUE			        ENGINE.GetCommandQueue()
#define CONSTANTBUFFER(cbtype)		ENGINE.GetConstantBuffer(cbtype)
#define TABLEDESCHEAP		        ENGINE.GetTableDescHeap()
#define DSBUFFER			        ENGINE.GetDepthStencilBuffer()


