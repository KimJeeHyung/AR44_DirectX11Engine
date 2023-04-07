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
    float fadeDeltaTime;
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

cbuffer ParticleSystem : register(b6)
{
    float4 particleColor;
    uint elementCount;
    float particleDeltaTime;
    float elapsedTime;  // �����ð�
}

//cbuffer Noise : register(b7)
//{
//    float4 NoiseSize;
//}