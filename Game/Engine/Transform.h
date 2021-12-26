#pragma once
#include "Component.h"

class EXPORTCLASS Transform : public Component
{
public:
	Transform();
	virtual ~Transform();

	virtual void FinalUpdate() override;
	void PushData();

public:
	// Parent 기준
	const vector3& GetLocalPosition() const { return _localPosition; }
	const vector3& GetLocalRotation() const { return _localRotation; }
	const vector3& GetLocalScale() const { return _localScale; }

	const matrix&  GetLocalToWorldMatrix() const { return _matWorld; }
	const vector3& GetWorldPosition() const { return _matWorld.Translation(); }

	const vector3& GetRight() const { return _matWorld.Right(); }
	const vector3& GetUp() const { return _matWorld.Up(); }
	const vector3& GetLook() const { return _matWorld.Backward(); }

	void SetLocalPosition(const vector3& position) { _localPosition = position; }
	void SetLocalRotation(const vector3& rotation) { _localRotation = rotation; }
	void SetLocalScale(const vector3& scale) { _localScale = scale; }

public:
	void SetParent(shared_ptr<Transform> parent) { _parent = parent; }
	weak_ptr<Transform> GetParent() const { return _parent; }

private:
	// Parent 기준
	vector3 _localPosition = {};
	vector3 _localRotation = {};
	vector3 _localScale = { 1.f, 1.f, 1.f };

	matrix _matLocal = {};
	matrix _matWorld = {};

	weak_ptr<Transform> _parent;
};

