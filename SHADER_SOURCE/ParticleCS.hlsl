#include "globals.hlsli"

RWStructuredBuffer<Particle> ParticleBuffer : register(u0);
RWStructuredBuffer<ParticleShared> ParticleSharedBuffer : register(u1);

// 각각의 스레드가 동기화할 데이터가 필요하다.
// 1024개가 최대 스레드 개수
[numthreads(128, 1, 1)]
void main(uint3 DTid : SV_DispatchThreadID)
{
    if (elementCount <= DTid.x)
        return;
    
    if (particleBuffer[DTid.x].active == 0)
    {
        while (0 < ParticleSharedBuffer[0].gActiveCount)
        {
            int originValue = ParticleSharedBuffer[0].gActiveCount;
            int exchange = originValue - 1;
            
            // 스레드 동기화
            // dest값을 exchange값으로 바꾸는 동안
            // 다른 스레드는 멈춘다.
            InterlockedExchange(ParticleSharedBuffer[0].gActiveCount, exchange, exchange);
            
            if (originValue == exchange)
            {
                particleBuffer[DTid.x].active = 1;
                break;
            }
        }
    }
    else // active == 1
    {
        particleBuffer[DTid.x].position += particleBuffer[DTid.x].direction *
            particleBuffer[DTid.x].speed * particleDeltaTime;
    }
}