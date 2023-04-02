#include "jhParticleSystem.h"
#include "jhMesh.h"
#include "jhResources.h"
#include "jhMaterial.h"
#include "jhStructedBuffer.h"
#include "jhTransform.h"
#include "jhGameObject.h"
#include "jhTexture.h"

namespace jh
{
	ParticleSystem::ParticleSystem() :
		BaseRenderer(eComponentType::ParticleSystem),
		mCount(100),
		mStartSize(Vector4::Zero),
		mEndSize(Vector4::Zero),
		mStartColor(Vector4::Zero),
		mEndColor(Vector4::Zero),
		mStartLifeTime(0.f)
	{
	}

	ParticleSystem::~ParticleSystem()
	{
		delete mBuffer;
		mBuffer = nullptr;
	}

	void ParticleSystem::Initialize()
	{
		mCS = Resources::Find<ParticleShader>(L"ParticleCS");

		std::shared_ptr<Mesh> point = Resources::Find<Mesh>(L"PointMesh");
		SetMesh(point);

		// Material ¼¼ÆÃ
		std::shared_ptr<Material> material = Resources::Find<Material>(L"ParticleMaterial");
		SetMaterial(material);

		std::shared_ptr<Texture> tex = Resources::Find<Texture>(L"CartoonSmoke");
		material->SetTexture(eTextureSlot::T0, tex);

		Particle particles[100] = {};
		Vector4 startPos = Vector4(-800.f, -450.f, 0.f, 0.f);
		for (size_t i = 0; i < mCount; i++)
		{
			particles[i].position = Vector4(0.f, 0.f, 20.f, 1.f);
			particles[i].active = 1;
			particles[i].direction = Vector4(cosf((float)i * (XM_2PI / (float)mCount)),
				sinf((float)i * (XM_2PI / (float)mCount)), 0.f, 1.f);

			particles[i].speed = 100.f;
		}

		mBuffer = new StructedBuffer();
		mBuffer->Create(sizeof(Particle), mCount, eSRVType::UAV, particles);
	}

	void ParticleSystem::Update()
	{
	}

	void ParticleSystem::FixedUpdate()
	{
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