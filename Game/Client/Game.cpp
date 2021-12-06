#include "pch.h"
#include "Game.h"

#include "Mesh.h"
#include "Shader.h"
#include "../Engine/CommandQueue.h"
#include "../Engine/Device.h"
#include "../Engine/RootSignature.h"

shared_ptr<Mesh> mesh = make_shared<Mesh>();
shared_ptr<Shader> shader = make_shared<Shader>();


void Game::Init(const WindowInfo& window)
{
	if(_engine == nullptr)
	{
		_engine = make_unique<Engine>();
	}
	
	_engine->Init(window);

	vector<Vertex> vec(3);
	vec[0].pos = vector3(0.f, 0.5f, 0.5f);
	vec[0].color = vector4(1.f, 0.f, 0.f, 1.f);

	vec[1].pos = vector3(0.5f, -0.5f, 0.5f);
	vec[1].color = vector4(0.f, 1.f, 0.f, 1.f);

	vec[2].pos = vector3(-0.5f, -0.5f, 0.5f);
	vec[2].color = vector4(0.f, 0.f, 1.f, 1.f);

	mesh->Init(_engine->GetDeivce()->GetDevice(), _engine->GetCommandQueue()->GetCmdList(), vec);
	shader->Init(_engine->GetDeivce()->GetDevice()
		, _engine->GetCommandQueue()->GetCmdList()
		, _engine->GetSignature()->GetSignature()
		, L"C:\\Users\\horon\\Documents\\GitHub\\dx12\\Game\\Resources\\Shader\\default.hlsli");
}

void Game::Update()
{
	_engine->RenderBegin();

	shader->Update();
	mesh->Render();

	_engine->RenderEnd();
}
