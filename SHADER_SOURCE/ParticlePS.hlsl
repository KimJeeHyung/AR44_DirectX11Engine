#include "globals.hlsli"

struct VSIn
{
    float4 Pos : POSITION;
    uint iInstance : SV_InstanceID;
};

struct VSOut
{
    float4 Pos : SV_Position;
};

float4 main(VSOut In) : SV_TARGET
{
    float4 outColor = (float4) 0.f;
    
    outColor = float4(1.f, 0.f, 0.f, 1.f);
    
	return outColor;
}