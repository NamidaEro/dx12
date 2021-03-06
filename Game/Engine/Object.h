#pragma once

enum class OBJECT_TYPE : uint8
{
	NONE,
	GAMEOBJECT, // PREFAB
	COMPONENT,
	MATERIAL,
	MESH,
	SHADER,
	TEXTURE,

	END
};

enum
{
	OBJECT_TYPE_COUNT = static_cast<uint8>(OBJECT_TYPE::END)
};

class EXPORTCLASS Object
{
public:
	Object(const OBJECT_TYPE& type);
	virtual ~Object();

	OBJECT_TYPE GetType() const { return _objectType; }

	void SetName(const wstring& name) { _name = name; }
	const wstring& GetName() const { return _name; }

	// TODO : Instantiate

protected:
	friend class Resources;
	virtual void Load(const wstring& path) { }
	virtual void Save(const wstring& path) { }

protected:
	OBJECT_TYPE _objectType = OBJECT_TYPE::NONE;
	wstring _name;
};

