#pragma once


#define EXPORTCLASS __declspec(dllexport)

struct WindowInfo
{
	HWND	hwnd;
	int32	width;
	int32	height;
	bool	isWindow;
};