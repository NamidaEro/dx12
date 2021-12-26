#include "pch.h"
#include "TestCameraScript.h"
#include "Transform.h"
#include "Camera.h"
#include "GameObject.h"
#include "Input.h"
#include "Timer.h"

TestCameraScript::TestCameraScript()
{
}

TestCameraScript::~TestCameraScript()
{
}

void TestCameraScript::LateUpdate()
{
	vector3 pos = GetTransform()->GetLocalPosition();

	if (GInput().GetButton(KEY_TYPE::W))
		pos += GetTransform()->GetLook() * _speed * GTimer().GetDeltaTime();

	if (GInput().GetButton(KEY_TYPE::S))
		pos -= GetTransform()->GetLook() * _speed * GTimer().GetDeltaTime();

	if (GInput().GetButton(KEY_TYPE::A))
		pos -= GetTransform()->GetRight() * _speed * GTimer().GetDeltaTime();

	if (GInput().GetButton(KEY_TYPE::D))
		pos += GetTransform()->GetRight() * _speed * GTimer().GetDeltaTime();

	if (GInput().GetButton(KEY_TYPE::Q))
	{
		vector3 rotation = GetTransform()->GetLocalRotation();
		rotation.x += GTimer().GetDeltaTime() * 0.5f;
		GetTransform()->SetLocalRotation(rotation);
	}

	if (GInput().GetButton(KEY_TYPE::E))
	{
		vector3 rotation = GetTransform()->GetLocalRotation();
		rotation.x -= GTimer().GetDeltaTime() * 0.5f;
		GetTransform()->SetLocalRotation(rotation);
	}

	GetTransform()->SetLocalPosition(pos);
}