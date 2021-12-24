#include "pch.h"
#include "Component.h"

#include "GameObject.h"

Component::Component(const COMPONENT_TYPE& type)
{
}

Component::~Component()
{
}

shared_ptr<GameObject> Component::GetGameObject()
{
    return _gameObject.lock();
}

shared_ptr<Transform> Component::GetTransform()
{
    return _gameObject.lock()->GetTransform();
}
