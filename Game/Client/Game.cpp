#include "pch.h"
#include "Game.h"

#include "Mesh.h"
#include "Shader.h"
#include "CommandQueue.h"
#include "Device.h"
#include "RootSignature.h"

shared_ptr<Mesh> mesh = make_shared<Mesh>();
shared_ptr<Shader> shader = make_shared<Shader>();


void Game::Init(const WindowInfo& window)
{
	Engine::Instance().Init(window);

	/*vector<Vertex> vec(6);
	vec[0].pos = vector3(-0.5f, 0.5f, 0.5f);
	vec[0].color = vector4(1.f, 0.f, 0.f, 1.f);
	vec[1].pos = vector3(0.5f, 0.5f, 0.5f);
	vec[1].color = vector4(1.f, 0.f, 0.f, 1.f);
	vec[2].pos = vector3(0.5f, -0.5f, 0.5f);
	vec[2].color = vector4(1.f, 0.f, 0.f, 1.f);

	vec[3].pos = vector3(0.5f, -0.5f, 0.5f);
	vec[3].color = vector4(1.f, 0.f, 0.f, 1.f);
	vec[4].pos = vector3(-0.5f, -0.5f, 0.5f);
	vec[4].color = vector4(1.f, 0.f, 0.f, 1.f);
	vec[5].pos = vector3(-0.5f, 0.5f, 0.5f);
	vec[5].color = vector4(1.f, 0.f, 0.f, 1.f);*/

	vector<Vertex> vertex(4);
	vertex[0].pos = vector3(-0.5f, 0.5f, 0.5f);
	vertex[0].color = vector4(1.f, 0.f, 0.f, 1.f);
	vertex[1].pos = vector3(0.5f, 0.5f, 0.5f);
	vertex[1].color = vector4(1.f, 0.f, 0.f, 1.f);
	vertex[2].pos = vector3(0.5f, -0.5f, 0.5f);
	vertex[2].color = vector4(1.f, 0.f, 0.f, 1.f);
	vertex[3].pos = vector3(-0.5f, -0.5f, 0.5f);
	vertex[3].color = vector4(1.f, 0.f, 0.f, 1.f);

	vector<uint32> index;
	index.push_back(0);
	index.push_back(1);
	index.push_back(2);
	index.push_back(0);
	index.push_back(2);
	index.push_back(3);

	mesh->Init(vertex, index);
	shader->Init(L"..\\Resources\\Shader\\default.hlsli");
}

void Game::Update()
{
	/*_engine->RenderBegin();

	shader->Update();
	mesh->Render();

	_engine->RenderEnd();*/

	Engine::Instance().RenderBegin();

	shader->Update();

	{
		Transform t;
		t.offset = vector4(0.f, 0.f, 0.f, 0.f);
		mesh->SetTransform(t);

		mesh->Render();
	}

	/*{
		Transform t;
		t.offset = vector4(0.f, 0.75f, 0.f, 0.f);
		mesh->SetTransform(t);

		mesh->Render();
	}*/

	Engine::Instance().RenderEnd();
}
