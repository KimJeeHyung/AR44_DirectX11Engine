#include "jhParticleSystem.h"
#include "jhMesh.h"
#include "jhResources.h"
#include "jhMaterial.h"
#include "jhStructedBuffer.h"
#include "jhTransform.h"
#include "jhGameObject.h"
#include "jhTexture.h"
#include "jhTime.h"

namespace jh
{
	ParticleSystem::ParticleSystem() :
		BaseRenderer(eComponentType::ParticleSystem),
		mCount(100),
		mStartSize(Vector4::Zero),
		mEndSize(Vector4::Zero),
		mStartColor(Vector4::Zero),
		mEndColor(Vector4::Zero),
		mStartLifeTime(0.f),
		mFrequency(1.f),
		mTime(0.f)
	{
	}

	ParticleSystem::~ParticleSystem()
	{
		delete mBuffer;
		mBuffer = nullptr;

		delete mSharedBuffer;
		mSharedBuffer = nullptr;
	}

	void ParticleSystem::Initialize()
	{
		mCS = Resources::Find<ParticleShader>(L"ParticleCS");

		std::shared_ptr<Mesh> point = Resources::Find<Mesh>(L"PointMesh");
		SetMesh(point);

		// Material 세팅
		std::shared_ptr<Material> material = Resources::Find<Material>(L"ParticleMaterial");
		SetMaterial(material);

		std::shared_ptr<Texture> tex = Resources::Find<Texture>(L"CartoonSmoke");
		material->SetTexture(eTextureSlot::T0, tex);

		Particle particles[100] = {};
		Vector4 startPos = Vector4(-800.f, -450.f, 0.f, 0.f);
		for (size_t i = 0; i < mCount; i++)
		{
			particles[i].position = Vector4(0.f, 0.f, 20.f, 1.f);
			particles[i].active = 0;
			particles[i].direction = Vector4(cosf((float)i * (XM_2PI / (float)mCount)),
				sinf((float)i * (XM_2PI / (float)mCount)), 0.f, 1.f);

			particles[i].speed = 100.f;
		}

		mBuffer = new StructedBuffer();
		mBuffer->Create(sizeof(Particle), mCount, eSRVType::UAV, particles);

		mSharedBuffer = new StructedBuffer();
		mSharedBuffer->Create(sizeof(ParticleShared), 1, eSRVType::UAV, nullptr, true);
	}

	void ParticleSystem::Update()
	{
	}

	void ParticleSystem::FixedUpdate()
	{
		// 파티클 생성 시간
		float aliveTime = 1.f / mFrequency;
		// 누적 시간
		mTime += Time::DeltaTime();
		if (aliveTime < mTime)
		{
			float f = (mTime / aliveTime);
			UINT iAliveCount = (UINT)f;
			mTime = f - std::floor(f);

			ParticleShared shared = { 5, };
			mSharedBuffer->SetData(&shared, 1);
		}
		else
		{
			ParticleShared shared = {};
			mSharedBuffer->SetData(&shared, 1);
		}

		renderer::ParticleSystemCB info = {};
		info.elementCount = mBuffer->GetStride();
		info.deltaTime = Time::DeltaTime();

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::ParticleSystem];
		cb->SetData(&info);
		cb->Bind(eShaderStage::CS);

		mCS->SetSharedStructedBuffer(mSharedBuffer);
		mCS->SetStructedBuffer(mBuffer);
		mCS->OnExcute();
	}

	void ParticleSystem::Render()
	{
		GetOwner()->GetComponent<Transform>()->SetConstantBuffer();
		mBuffer->BindSRV(eShaderStage::VS, 15);
		mBuffer->BindSRV(eShaderStage::GS, 15);
		mBuffer->BindSRV(eShaderStage::PS, 15);

		GetMaterial()->Bind();
		GetMesh()->RenderInstanced(mCount);

		mBuffer->Clear();
	}
}