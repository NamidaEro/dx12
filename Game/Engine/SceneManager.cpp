#include "pch.h"
#include "SceneManager.h"

#include "Camera.h"
#include "Scene.h"
#include "Resources.h"
#include "Transform.h"
#include "MeshRenderer.h"

#include "TestCameraScript.h"

void SceneManager::Update()
{
	if (_activeScene == nullptr) { return; }

	_activeScene->Update();
	_activeScene->LateUpdate();
	_activeScene->FinalUpdate();
}

void SceneManager::Render()
{
	if (_activeScene == nullptr) { return; }

	const vector<shared_ptr<GameObject>>& gameObjects = _activeScene->GetGameObjects();
	for (auto& gameObject : gameObjects)
	{
		if (gameObject->GetCamera() == nullptr)
		{
			continue;
		}

		gameObject->GetCamera()->Render();
	}
}

void SceneManager::LoadScene(const wstring& sceneName)
{
	_activeScene = LoadTestScene();

	_activeScene->Awake();
	_activeScene->Start();
}

shared_ptr<Scene> SceneManager::LoadTestScene()
{
	shared_ptr<Scene> scene = make_shared<Scene>();
#pragma region Camera
    const shared_ptr<GameObject> camera = make_shared<GameObject>();
	camera->AddComponent(make_shared<Transform>());
	camera->AddComponent(make_shared<Camera>()); // Near=1, Far=1000, FOV=45µµ
	camera->AddComponent(make_shared<TestCameraScript>());
	camera->GetTransform()->SetLocalPosition(vector3(0.f, 100.f, 0.f));
	scene->AddGameObject(camera);
#pragma endregion
	
#pragma region Sphere
	{
        const shared_ptr<GameObject> sphere = make_shared<GameObject>();
		sphere->AddComponent(make_shared<Transform>());
		sphere->GetTransform()->SetLocalScale(vector3(100.f, 100.f, 100.f));
		sphere->GetTransform()->SetLocalPosition(vector3(0.f, 100.f, 200.f));
		shared_ptr<MeshRenderer> meshRenderer = make_shared<MeshRenderer>();
		{
            const shared_ptr<Mesh> sphereMesh = GResources().LoadSphereMesh();
			meshRenderer->SetMesh(sphereMesh);
		}
		{
            const shared_ptr<Shader> shader = make_shared<Shader>();
            const shared_ptr<Texture> texture = make_shared<Texture>();
			shader->Init(L"..\\Resources\\Shader\\default.hlsli");
			texture->Init(L"..\\Resources\\Texture\\veigar.jpg");
            const shared_ptr<Material> material = make_shared<Material>();
			material->SetShader(shader);
			material->SetTexture(0, texture);
			meshRenderer->SetMaterial(material);
		}
		sphere->AddComponent(meshRenderer);
		scene->AddGameObject(sphere);
	}
#pragma endregion

#pragma region Cube
	{
        const shared_ptr<GameObject> sphere = make_shared<GameObject>();
		sphere->AddComponent(make_shared<Transform>());
		sphere->GetTransform()->SetLocalScale(vector3(100.f, 100.f, 100.f));
		sphere->GetTransform()->SetLocalPosition(vector3(150.f, 100.f, 200.f));
        const shared_ptr<MeshRenderer> meshRenderer = make_shared<MeshRenderer>();
		{
            const shared_ptr<Mesh> sphereMesh = GResources().LoadCubeMesh();
			meshRenderer->SetMesh(sphereMesh);
		}
		{
            const shared_ptr<Shader> shader = make_shared<Shader>();
            const shared_ptr<Texture> texture = make_shared<Texture>();
			shader->Init(L"..\\Resources\\Shader\\default.hlsli");
			texture->Init(L"..\\Resources\\Texture\\veigar.jpg");
            const shared_ptr<Material> material = make_shared<Material>();
			material->SetShader(shader);
			material->SetTexture(0, texture);
			meshRenderer->SetMaterial(material);
		}
		sphere->AddComponent(meshRenderer);
		scene->AddGameObject(sphere);
	}
#pragma endregion


	return scene;
}
