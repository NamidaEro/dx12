#pragma once
#include "Component.h"

struct MatrixTransform
{
	vector4 offset;
};

class EXPORTCLASS Transform : public Component
{
public:
	Transform();
	virtual ~Transform();

	// TODO : �°� Parent/Child ����

private:
	// TODO : World ��ġ ����

};

