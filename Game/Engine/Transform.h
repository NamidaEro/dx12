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

	// TODO : 온갖 Parent/Child 관계

private:
	// TODO : World 위치 관련

};

