#pragma once

class GameObject;
class Scene
{
public:
	void Awake();
	void Start();
	void Render();
	void Update();
	void LateUpdate();
	void FinalUpdate();

	void AddGameObject(shared_ptr<GameObject> gameObject);
	void RemoveGameObject(shared_ptr<GameObject> gameObject);

	const vector<shared_ptr<GameObject>>& GetGameObjects() const { return _gameObjects; }

private:
	void PushLightData();

private:
	vector<shared_ptr<GameObject>> _gameObjects;

};

