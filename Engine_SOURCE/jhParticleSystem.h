#pragma once
#include "jhBaseRenderer.h"
#include "jhParticleShader.h"

namespace jh
{
	class ParticleSystem : public BaseRenderer
	{
	public:
		ParticleSystem();
		~ParticleSystem();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

	private:
		class StructedBuffer* mBuffer;
		class StructedBuffer* mSharedBuffer;

		std::shared_ptr<graphics::ParticleShader> mCS;
		renderer::ParticleSystemCB mCBData;

		UINT mCount;
		Vector4 mStartSize;
		Vector4 mEndSize;
		Vector4 mStartColor;
		Vector4 mEndColor;
		float mStartLifeTime;
		float mFrequency;
		float mTime;
	};
}
