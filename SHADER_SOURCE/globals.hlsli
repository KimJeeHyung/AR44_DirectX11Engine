#include "Light.hlsli"
cbuffer Transform : register(b0)
{
    row_major matrix world;
    row_major matrix view;
    row_major matrix projection;
}

cbuffer MaterialData : register(b1)
{
    int cbiData;
    float cbfData;
    float2 cbxy;
    float3 cbxyz;
    float4 cbxyzw;
    matrix cbmat;
}

cbuffer Grid : register(b2)
{
    float4 gCameraPosition;
    float2 gCameraScale;
    float2 gResolution;
}

cbuffer Fade : register(b3)
{
    float4 fCameraPosition;
    float2 fCameraScale;
    float2 fResolution;
    float deltaTime;
    float3 padding;
}

cbuffer Animation : register(b4)
{
    float2 leftTop;
    float2 spriteSize;
    float2 offset;
    float2 atlasSize;

    uint animationType;
}

cbuffer NumberOfLight : register(b5)
{
    uint numberOfLight;
}

SamplerState pointSampler : register(s0);
SamplerState linearSampler : register(s1);
SamplerState anisotropicSampler : register(s2);

StructuredBuffer<LightAttribute> lightAttributes : register(t13);

Texture2D defaultTexture : register(t0);
// Atlas Texture
Texture2D atlasTexture : register(t12);

void CalculateLight(in out LightColor pLightColor, float3 position, int idx)
{
    if (0 == lightAttributes[idx].type)
    {
        pLightColor.diffuse += lightAttributes[idx].color.diffuse;
    }
    else if (1 == lightAttributes[idx].type)
    {
        float length = distance(lightAttributes[idx].position.xy, position.xy);
        
        if (length < lightAttributes[idx].radius)
        {
            float ratio = 1.f - (length / lightAttributes[idx].radius);
            pLightColor.diffuse += lightAttributes[idx].color.diffuse * ratio;// * cos(time);
        }
    }
}