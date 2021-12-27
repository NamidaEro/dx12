#pragma once

#ifdef _EXPORT
#define EXPORTCLASS __declspec(dllexport)
#else
#define EXPORTCLASS
#endif

#define _HAS_STD_BYTE 0

#include <Windows.h>
#include <tchar.h>
#include <memory>
#include <string>
#include <vector>
#include <array>
#include <list>
#include <map>

using namespace std;

#include <filesystem>

namespace fs = std::filesystem;

#include "d3dx12.h"
#include "SimpleMath.h"
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

#include <DirectXTex/DirectXTex.h>
#include <DirectXTex/DirectXTex.inl>
#include "SimpleMath.inl"

#pragma comment(lib, "d3d12")
#pragma comment(lib, "dxgi")
#pragma comment(lib, "dxguid")
#pragma comment(lib, "d3dcompiler")

#ifdef _DEBUG
#pragma comment(lib, "DirectXTex\\DirectXTex_debug.lib")
#else
#pragma comment(lib, "DirectXTex\\DirectXTex.lib")
#endif

using int8			= __int8;
using int16			= __int16;
using int32			= __int32;
using int64			= __int64;
using uint8			= unsigned __int8;
using uint16		= unsigned __int16;
using uint32		= unsigned __int32;
using uint64		= unsigned __int64;
using vector2		= DirectX::SimpleMath::Vector2;
using vector3		= DirectX::SimpleMath::Vector3;
using vector4		= DirectX::SimpleMath::Vector4;
using matrix		= DirectX::SimpleMath::Matrix;

#include "Macros.h"
#include "Enums.h"
#include "Struct.h"

class EXPORTCLASS Engine;
extern EXPORTCLASS unique_ptr<Engine> g_engine;

class EXPORTCLASS SceneManager;
extern EXPORTCLASS unique_ptr<SceneManager> g_sceneManager;

class EXPORTCLASS Input;
extern EXPORTCLASS unique_ptr<Input> g_input;

class EXPORTCLASS Timer;
extern EXPORTCLASS unique_ptr<Timer> g_timer;

class EXPORTCLASS Resources;
extern EXPORTCLASS unique_ptr<Resources> g_resources;

EXPORTCLASS
Engine& GEngine();

EXPORTCLASS
SceneManager& GSceneManager();

EXPORTCLASS
Input& GInput();

EXPORTCLASS
Timer& GTimer();

EXPORTCLASS
Resources& GResources();

#pragma warning(disable: 4251)
#pragma warning(disable: 4172)