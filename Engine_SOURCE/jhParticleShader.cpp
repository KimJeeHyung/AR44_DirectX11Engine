#include "jhParticleShader.h"
#include "jhRenderer.h"
#include "jhConstantBuffer.h"
#include "jhTime.h"

namespace jh::graphics
{
	ParticleShader::ParticleShader() :
		ComputeShader(128,1,1),
		mBuffer(nullptr)
	{
	}

	ParticleShader::~ParticleShader()
	{
	}

	void ParticleShader::Binds()
	{
		mBuffer->BindUAV(eShaderStage::CS, 0);

		mGroupX = mBuffer->GetStride() / mThreadGroupCountX;
		mGroupY = 1;
		mGroupZ = 1;
	}

	void ParticleShader::Clear()
	{
		mBuffer->Clear();
	}

	void ParticleShader::SetStructedBuffer(StructedBuffer* buffer)
	{
		mBuffer = buffer;

		renderer::ParticleSystemCB info = {};
		info.elementCount = mBuffer->GetStride();
		info.deltaTime = Time::DeltaTime();

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::ParticleSystem];
		cb->SetData(&cb);
		cb->Bind(eShaderStage::CS);
	}
}
