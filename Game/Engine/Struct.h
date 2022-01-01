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
	Vertex() = default;

	Vertex(vector3 p, vector2 u, vector3 n, vector3 t)
		: pos(p), uv(u), normal(n), tangent(t)
	{
	}

	vector3 pos;
	vector2 uv;
	vector3 normal;
	vector3 tangent;
};


struct TransformParams
{
	matrix matWorld;
	matrix matView;
	matrix matProjection;
	matrix matWV;
	matrix matWVP;
};