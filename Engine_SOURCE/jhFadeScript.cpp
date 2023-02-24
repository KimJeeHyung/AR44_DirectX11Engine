#include "jhFadeScript.h"
#include "jhTransform.h"
#include "jhGameObject.h"
#include "jhApplication.h"
#include "jhConstantBuffer.h"
#include "jhRenderer.h"
#include "jhTime.h"
#include "jhInput.h"

extern jh::Application application;

namespace jh
{
	FadeScript::FadeScript() :
		Script(),
		mCamera(nullptr),
		mAlpha(0.f),
		mIsFadeOut(false),
		mDeltaTime(0.f),
		mFadeTime(2.f)
	{
	}

	FadeScript::~FadeScript()
	{
	}

	void FadeScript::Initialize()
	{
		mCamera = renderer::cameras[0];
	}

	void FadeScript::Update()
	{
		if (mCamera == nullptr)
			return;

		GameObject* gameObj = mCamera->GetOwner();
		Transform* tr = gameObj->GetComponent<Transform>();

		Vector3 cameraPos = tr->GetPosition();
		Vector4 position = Vector4(cameraPos.x, cameraPos.y, cameraPos.z, 1.f);

		float scale = mCamera->GetScale();

		RECT winRect;
		GetClientRect(application.GetHwnd(), &winRect);
		float width = winRect.right - winRect.left;
		float height = winRect.bottom - winRect.top;
		Vector2 resolution(width, height);

		if (Input::GetKeyState(eKeyCode::F) == eKeyState::DOWN)
		{
			// ¾îµÎ¿öÁü
			mIsFadeOut = true;
			mDeltaTime = 0.f;
		}
		else if (Input::GetKeyState(eKeyCode::G) == eKeyState::DOWN)
		{
			// ¹à¾ÆÁü
			mIsFadeOut = false;
			mDeltaTime = 1.f;
		}

		if(mIsFadeOut == true)
			mDeltaTime += Time::DeltaTime() / mFadeTime;
		else
			mDeltaTime -= Time::DeltaTime() / mFadeTime;

		// »ó¼ö ¹öÆÛ
		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Fade];
		renderer::FadeCB data;
		data.cameraPosition = position;
		data.cameraScale = Vector2(scale, scale);
		data.resolution = resolution;
		data.deltaTime = mDeltaTime;
		data.padding = Vector3(0.f, 0.f, 0.f);

		cb->Bind(&data);
		cb->SetPipeline(eShaderStage::VS);
		cb->SetPipeline(eShaderStage::PS);
	}

	void FadeScript::FixedUpdate()
	{
	}

	void FadeScript::Render()
	{
	}
}