#include "pch.h"
#include "Game.h"

#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "CommandQueue.h"
#include "Input.h"
#include "Timer.h"
#include "GameObject.h"
#include "MeshRenderer.h"

shared_ptr<GameObject> gameObject = make_shared<GameObject>();

void Game::Init(const WindowInfo& window)
{
	GEngine().Init(window);
	
	vector<Vertex> vec(4);
	vec[0].pos = vector3(-0.5f, 0.5f, 0.5f);
	vec[0].color = vector4(1.f, 0.f, 0.f, 1.f);
	vec[0].uv = vector2(0.f, 0.f);

	vec[1].pos = vector3(0.5f, 0.5f, 0.5f);
	vec[1].color = vector4(0.f, 1.f, 0.f, 1.f);
	vec[1].uv = vector2(1.f, 0.f);

	vec[2].pos = vector3(0.5f, -0.5f, 0.5f);
	vec[2].color = vector4(0.f, 0.f, 1.f, 1.f);
	vec[2].uv = vector2(1.f, 1.f);

	vec[3].pos = vector3(-0.5f, -0.5f, 0.5f);
	vec[3].color = vector4(0.f, 1.f, 0.f, 1.f);
	vec[3].uv = vector2(0.f, 1.f);

	vector<uint32> index;
	index.push_back(0);
	index.push_back(1);
	index.push_back(2);

	index.push_back(0);
	index.push_back(2);
	index.push_back(3);

	gameObject->Init();

	shared_ptr<MeshRenderer> meshRenderer = make_shared<MeshRenderer>();

	{
		shared_ptr<Mesh> mesh = make_shared<Mesh>();
		mesh->Init(vec, index);
		meshRenderer->SetMesh(mesh);
	}

	{
		shared_ptr<Shader> shader = make_shared<Shader>();
		shared_ptr<Texture> texture = make_shared<Texture>();
		shader->Init(L"..\\Resources\\Shader\\default.hlsli");
		texture->Init(L"..\\Resources\\Texture\\veigar.jpg");
		shared_ptr<Material> material = make_shared<Material>();
		material->SetShader(shader);
		material->SetFloat(0, 0.3f);
		material->SetFloat(1, 0.4f);
		material->SetFloat(2, 0.3f);
		material->SetTexture(0, texture);
		meshRenderer->SetMaterial(material);
	}

	gameObject->AddComponent(meshRenderer);

	GEngine().GetCommandQueue()->WaitSync();
}

void Game::Update()
{
	GEngine().Update();
	GEngine().RenderBegin();
	gameObject->Update();
	GEngine().RenderEnd();
}
