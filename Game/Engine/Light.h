#pragma once
#include "Component.h"

enum class LIGHT_TYPE : uint8
{
    DIRECTIONAL_LIGHT,
    POINT_LIGHT,
    SPOT_LIGHT,
};

struct LightColor
{
    vector4     diffuse;
    vector4     ambient;
    vector4     specular;
};

struct LightInfo
{
    LightColor  color;
    vector4     position;
    vector4     direction;
    int32       lightType;
    float       range;
    float       angle;
    int32       padding;
};

struct LightParams
{
    uint32 lightCount;
    vector3 padding;
    LightInfo lights[50];
};

class EXPORTCLASS Light : public Component
{
public:
    Light();
    virtual ~Light();

    virtual void FinalUpdate() override;

public:
    const LightInfo& GetLightInfo() const { return _lightInfo; }

    void SetLightDirection(const vector3& dir) { _lightInfo.direction = dir; }

    void SetDiffuse(const vector3& diffuse) { _lightInfo.color.diffuse = diffuse; }
    void SetAmbient(const vector3& ambient) { _lightInfo.color.ambient = ambient; }
    void SetSpecular(const vector3& specular) { _lightInfo.color.specular = specular; }

    void SetLightType(const LIGHT_TYPE& type) { _lightInfo.lightType = static_cast<int32>(type); }
    void SetLightRange(const float& range) { _lightInfo.range = range; }
    void SetLightAngle(const float& angle) { _lightInfo.angle = angle; }

private:
    LightInfo _lightInfo = {};
};

