#pragma once

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
	vector2 uv;
};
