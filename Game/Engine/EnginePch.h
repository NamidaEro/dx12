#pragma once

#ifdef _EXPORT
#define EXPORTCLASS __declspec(dllexport)
#else
#define EXPORTCLASS
#endif

#include <Windows.h>
#include <tchar.h>
#include <memory>
#include <string>
#include <vector>
#include <array>
#include <list>
#include <map>

using namespace std;

#include "d3dx12.h"
#include <d3d12.h>
#include <wrl.h>
#include <d3dcompiler.h>
#include <dxgi.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>

#include "Singleton.h"

using namespace DirectX;
using namespace DirectX::PackedVector;
using namespace Microsoft::WRL;

#pragma comment(lib, "d3d12")
#pragma comment(lib, "dxgi")
#pragma comment(lib, "dxguid")
#pragma comment(lib, "d3dcompiler")

using int8			= __int8;
using int16			= __int16;
using int32			= __int32;
using int64			= __int64;
using uint8			= unsigned __int8;
using uint16		= unsigned __int16;
using uint32		= unsigned __int32;
using uint64		= unsigned __int64;
using vector2		= XMFLOAT2;
using vector3		= XMFLOAT3;
using vector4		= XMFLOAT4;
using matrix		= XMMATRIX;

struct WindowInfo
{
	HWND	hwnd;
	int32	width;
	int32	height;
	bool	isWindow;
};

struct Vertex
{
	vector3 pos;
	vector4 color;
};

struct Transform
{
	vector4 offset;
};

enum class CBV_REGISTER
{
	b0,
	b1,
	b2,
	b3,
	b4,

	END
};

enum
{
	SWAP_CHAIN_BUFFER_COUNT = 2,
	CBV_REGISTER_COUNT = CBV_REGISTER::END,
	REGISTER_COUNT = CBV_REGISTER::END,
};



class EXPORTCLASS Engine;
extern Engine* GlobalEngine;

#include "Macros.h"