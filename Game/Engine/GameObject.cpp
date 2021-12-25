#include "pch.h"
#include "GameObject.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "MonoBehaviour.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

void GameObject::Init()
{
	const auto transform = make_shared<Transform>();
    AddComponent(transform);
}

void GameObject::Awake()
{
	for (shared_ptr<Component>& component : _components)
	{
		if (component)
		{
			component->Awake();
		}
	}

	for (const shared_ptr<MonoBehaviour>& script : _scripts)
	{
		script->Awake();
	}
}

void GameObject::Start()
{
	for (shared_ptr<Component>& component : _components)
	{
		if (component)
		{
			component->Start();
		}
	}

	for (const shared_ptr<MonoBehaviour>& script : _scripts)
	{
		script->Start();
	}
}

void GameObject::Update()
{
	for (shared_ptr<Component>& component : _components)
	{
		if (component)
		{
			component->Update();
		}
	}

	for (const shared_ptr<MonoBehaviour>& script : _scripts)
	{
		script->Update();
	}
}

void GameObject::LateUpdate()
{
	for (shared_ptr<Component>& component : _components)
	{
		if (component)
		{
			component->LateUpdate();
		}
	}

	for (const shared_ptr<MonoBehaviour>& script : _scripts)
	{
		script->LateUpdate();
	}
}

shared_ptr<Transform> GameObject::GetTransform()
{
	constexpr uint8 index = static_cast<uint8>(COMPONENT_TYPE::TRANSFORM);
	return static_pointer_cast<Transform>(_components[index]);
}

void GameObject::AddComponent(shared_ptr<Component> component)
{
	component->SetGameObject(shared_from_this());

	const uint8 index = static_cast<uint8>(component->GetType());
	if (index < FIXED_COMPONENT_COUNT)
	{
		_components[index] = component;
	}
	else
	{
		const auto monoBehaviour = static_pointer_cast<MonoBehaviour>(component);
		_scripts.push_back(monoBehaviour);
	}
}
