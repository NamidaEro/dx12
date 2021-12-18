#pragma once

#define _HAS_STD_BYTE 0

#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#pragma comment(lib, "Engine.lib")

#include <vector>
#include <memory>
