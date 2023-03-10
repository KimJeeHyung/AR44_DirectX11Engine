#include "jhAnimation.h"
#include "jhTime.h"
#include "jhRenderer.h"

namespace jh
{
	Animation::Animation() :
		mAnimator(nullptr),
		mAtlas(nullptr),
		mSpriteSheet{},
		mIndex(-1),
		mTime(0.f),
		mbComplete(false)
	{
	}

	Animation::~Animation()
	{
	}

	void Animation::Update()
	{
		if (mbComplete)
			return;

		// 시간 체크
		mTime += Time::DeltaTime();

		// 누적 시간이 해당 프레임의 유지시간을 넘어서면 다음 프레임으로 이동
		if (mSpriteSheet[mIndex].duration < mTime)
		{
			mTime = 0.f;
			++mIndex;

			if (mSpriteSheet.size() <= mIndex)
			{
				mbComplete = true;
				mIndex = mSpriteSheet.size() - 1;
			}
		}
	}

	void Animation::FixedUpdate()
	{
	}

	void Animation::Render()
	{
	}

	void Animation::Create(const std::wstring& name, std::shared_ptr<Texture> atlas,
		Vector2 leftTop, Vector2 size, Vector2 offset,
		UINT spriteLegth, float duration)
	{
		mAnimationName = name;

		mAtlas = atlas;
		float width = (float)atlas->GetWidth();
		float height = (float)atlas->GetHeight();

		for (size_t i = 0; i < spriteLegth; i++)
		{
			// API와는 다르게 0 ~ 1 사이의 비율좌표로 위치를 표현해야 한다.
			Sprite sprite = {};
			sprite.leftTop = Vector2((leftTop.x + (size.x * (float)i)) / width, leftTop.y / height);

			sprite.size = Vector2(size.x / width, size.y / height);
			sprite.offset = offset;
			sprite.duration = duration;
			sprite.atlasSize = Vector2(200.f / width, 200.f / height);

			mSpriteSheet.push_back(sprite);
		}
	}

	void Animation::BindShader()
	{
		mAtlas->BindShader(eShaderStage::PS, 12);

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Animation];

		renderer::AnimationCB info = {};
		info.type = (UINT)eAnimationType::SecondDimension;
		info.leftTop = mSpriteSheet[mIndex].leftTop;
		info.offset = mSpriteSheet[mIndex].offset;
		info.size = mSpriteSheet[mIndex].size;
		info.atlasSize = mSpriteSheet[mIndex].atlasSize;

		cb->Bind(&info);
		cb->SetPipeline(eShaderStage::PS);
	}

	void Animation::Reset()
	{
		mTime = 0.f;
		mIndex = 0;
		mbComplete = false;
	}

	void Animation::Clear()
	{
	}
}
