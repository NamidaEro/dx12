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


	vector<Vertex> vec(3);
	vec[0].pos = vector3(0.f, 0.5f, 0.5f);
	vec[0].color = vector4(1.f, 0.f, 0.f, 1.f);

	vec[1].pos = vector3(0.5f, -0.5f, 0.5f);
	vec[1].color = vector4(0.f, 1.f, 0.f, 1.f);

	vec[2].pos = vector3(-0.5f, -0.5f, 0.5f);
	vec[2].color = vector4(0.f, 0.f, 1.f, 1.f);

	mesh->Init(vec);
	shader->Init(L"C:\\Users\\horon\\Documents\\GitHub\\dx12\\Game\\Resources\\Shader\\default.hlsli");
}

void Game::Update()
{
	/*_engine->RenderBegin();

	shader->Update();
	mesh->Render();

	_engine->RenderEnd();*/

	Engine::Instance().RenderBegin();

	shader->Update();
	mesh->Render();

	Engine::Instance().RenderEnd();
}
