#pragma once
#include "Object.h"

class GameObject;
class Transform;
class EXPORTCLASS Component : public Object
{
public:
	Component(const COMPONENT_TYPE& type);
	virtual ~Component();

public:
	virtual void Awake() { }
	virtual void Start() { }
	virtual void Update() { }
	virtual void LateUpdate() { }
	virtual void FinalUpdate() { }

public:
	COMPONENT_TYPE GetType() const { return _type; }
	bool IsValid() const { return _gameObject.expired() == false; }

	shared_ptr<GameObject> GetGameObject();
	shared_ptr<Transform> GetTransform();

private:
	friend class GameObject;
	void SetGameObject(shared_ptr<GameObject> gameObject) { _gameObject = gameObject; }

protected:
	COMPONENT_TYPE _type;
	weak_ptr<GameObject> _gameObject;
};

