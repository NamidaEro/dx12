#include "pch.h"
#include "Material.h"

#include "Engine.h"
#include "ConstantBuffer.h"
#include "Texture.h"
#include "Shader.h"

void Material::Update()
{
	CONSTANTBUFFER(CONSTANT_BUFFER_TYPE::MATERIAL)->PushData(&_params, sizeof(_params));
	
	for (size_t i = 0; i < _textures.size(); i++)
	{
		if (_textures[i] == nullptr) { continue; }

		SRV_REGISTER reg = SRV_REGISTER(static_cast<int8>(SRV_REGISTER::t0) + i);
		TABLEDESCHEAP->SetSRV(_textures[i]->GetCpuHandle(), reg);
	}
	
	_shader->Update();
}
