#pragma once
#include "Texture.h"
#include "Shader.h"

enum
{
	MATERIAL_INT_COUNT = 5,
	MATERIAL_FLOAT_COUNT = 5,
	MATERIAL_TEXTURE_COUNT = 5,
};

struct MaterialParams
{
	void SetInt(const uint8& index, const int32& value) { intParams[index] = value; }
	void SetFloat(const uint8& index, const float& value) { floatParams[index] = value; }

	std::array<int32, MATERIAL_INT_COUNT> intParams;
	std::array<float, MATERIAL_FLOAT_COUNT> floatParams;
};

class Material
{
public:
	shared_ptr<Shader> GetShader() const { return _shader; }

	void SetShader(shared_ptr<Shader> shader) { _shader = shader; }
	void SetInt(const uint8& index, const int32& value) { _params.SetInt(index, value); }
	void SetFloat(const uint8& index, const float& value) { _params.SetFloat(index, value); }
	void SetTexture(const uint8& index, shared_ptr<Texture> texture) { _textures[index] = texture; }

	void PushData();

private:
    shared_ptr<Shader>									_shader = nullptr;
	MaterialParams										_params = {};
	std::array<shared_ptr<Texture>, MATERIAL_TEXTURE_COUNT>	_textures;
};

