#include "pch.h"
#include "Transform.h"

#include "Engine.h"
#include "Camera.h"

Transform::Transform() : Component(COMPONENT_TYPE::TRANSFORM)
{

}

Transform::~Transform()
{

}

void Transform::FinalUpdate()
{
	matrix matScale = matrix::CreateScale(_localScale);
	matrix matRotation = matrix::CreateRotationX(_localRotation.x);
	matRotation *= matrix::CreateRotationY(_localRotation.y);
	matRotation *= matrix::CreateRotationZ(_localRotation.z);

    const matrix matTranslation = matrix::CreateTranslation(_localPosition);

	_matLocal = matScale * matRotation * matTranslation;
	_matWorld = _matLocal;

    const shared_ptr<Transform> parent = GetParent().lock();
	if (parent != nullptr)
	{
		_matWorld *= parent->GetLocalToWorldMatrix();
	}
}

void Transform::PushData()
{
	matrix matWVP = _matWorld * Camera::S_MatView * Camera::S_MatProjection;
	CONSTANTBUFFER(CONSTANT_BUFFER_TYPE::TRANSFORM)->PushData(&matWVP, sizeof(matWVP));
}