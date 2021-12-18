#include "pch.h"
#include "Game.h"

#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "CommandQueue.h"

shared_ptr<Mesh> mesh = make_shared<Mesh>();
shared_ptr<Shader> shader = make_shared<Shader>();
shared_ptr<Texture> texture = make_shared<Texture>();

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

	mesh->Init(vec, index);
	shader->Init(L"..\\Resources\\Shader\\default.hlsli");
	texture->Init(L"..\\Resources\\Texture\\veigar.jpg");

	GEngine().GetCommandQueue()->WaitSync();
}

void Game::Update()
{
	/*_engine->RenderBegin();

	shader->Update();
	mesh->Render();

	_engine->RenderEnd();*/



	GEngine().RenderBegin();

	shader->Update();

	{
		Transform t;
		t.offset = vector4(0.25f, 0.25f, 0.2f, 0.f);
		mesh->SetTransform(t);

		mesh->SetTexture(texture);

		mesh->Render();
	}

	{
		Transform t;
		t.offset = vector4(-0.25f, -0.25f, 0.1f, 0.f);
		mesh->SetTransform(t);

		mesh->SetTexture(texture);

		mesh->Render();
	}

	GEngine().RenderEnd();
}
