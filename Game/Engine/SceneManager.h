#pragma once

class Scene;
class EXPORTCLASS SceneManager : public Singleton<SceneManager>
{
public:
    void Update();
    void Render();
    void LoadScene(const wstring& sceneName);

public:
    shared_ptr<Scene> GetActiveScene() const { return _activeScene; }

private:
    shared_ptr<Scene> LoadTestScene();

private:
    shared_ptr<Scene> _activeScene;
};

