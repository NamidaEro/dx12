#pragma once


#define EXPORTCLASS __declspec(dllexport)

struct WindoInfo
{
	HWND	hwnd;
	int32	width;
	int32	height;
	bool	isWindow;
};