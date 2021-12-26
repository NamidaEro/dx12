#include "pch.h"
#include "Camera.h"

#include "Engine.h"
#include "Transform.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "MeshRenderer.h"

matrix Camera::S_MatView;
matrix Camera::S_MatProjection;

Camera::Camera() : Component(COMPONENT_TYPE::CAMERA)
{
}

Camera::~Camera()
{
}

void Camera::FinalUpdate()
{
	_matView = GetTransform()->GetLocalToWorldMatrix().Invert();

    const float width = static_cast<float>(GEngine().GetWindow().width);
    const float height = static_cast<float>(GEngine().GetWindow().height);

	if (_type == PROJECTION_TYPE::PERSPECTIVE)
	{
		_matProjection = ::XMMatrixPerspectiveFovLH(_fov, width / height, _near, _far);
	}
	else
	{
		_matProjection = ::XMMatrixOrthographicLH(width * _scale, height * _scale, _near, _far);
	}

	S_MatView = _matView;
	S_MatProjection = _matProjection;
}

void Camera::Render()
{
    const shared_ptr<Scene> scene = GSceneManager().GetActiveScene();

	// TODO : Layer ±¸ºÐ
	const vector<shared_ptr<GameObject>>& gameObjects = scene->GetGameObjects();

	for (auto& gameObject : gameObjects)
	{
		if (gameObject->GetMeshRenderer() == nullptr)
		{
			continue;
		}

		gameObject->GetMeshRenderer()->Render();
	}
}
