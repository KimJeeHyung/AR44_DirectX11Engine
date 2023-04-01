#include "globals.hlsli"

RWStructuredBuffer<Particle> ParticleBuffer : register(u0);

[numthreads(128, 1, 1)]
void main(uint3 DTid : SV_DispatchThreadID)
{
    if (elementCount <= DTid.x)
        return;
    
    particleBuffer[DTid.x].position += particleBuffer[DTid.x].direction *
    particleBuffer[DTid.x].speed * particleDeltaTime;
}