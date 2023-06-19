#include "jhJudgeScript.h"
#include "jhTransform.h"
#include "jhGameObject.h"
#include "jhInput.h"
#include "jhTime.h"
#include "jhAnimator.h"

namespace jh
{
	JudgeScript::JudgeScript() :
		Script(),
		mAnimator(nullptr)
	{
	}

	JudgeScript::~JudgeScript()
	{
	}

	void JudgeScript::Initialize()
	{
		mAnimator = GetOwner()->GetComponent<Animator>();

		bindEvent();
	}

	void JudgeScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();

		if (Input::GetKeyState(eKeyCode::R) == eKeyState::PRESSED)
		{
			Vector3 rot = tr->GetRotation();
			rot.z += 10.f * Time::DeltaTime();
			tr->SetRotation(rot);
		}

		if (Input::GetKey(eKeyCode::RIGHT))
		{
			Vector3 pos = tr->GetPosition();
			pos.x += 6.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		if (Input::GetKey(eKeyCode::LEFT))
		{
			Vector3 pos = tr->GetPosition();
			pos.x -= 6.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}

		if (Input::GetKey(eKeyCode::DOWN))
		{
			Vector3 pos = tr->GetPosition();
			pos.y -= 6.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		if (Input::GetKey(eKeyCode::UP))
		{
			Vector3 pos = tr->GetPosition();
			pos.y += 6.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}

		if (Input::GetKey(eKeyCode::N_1))
		{
			mAnimator->Play(L"JudgeIdle", true);
		}
		if (Input::GetKey(eKeyCode::N_2))
		{
			mAnimator->Play(L"JudgeIdleTalk", true);
		}
		if (Input::GetKey(eKeyCode::N_3))
		{
			mAnimator->Play(L"JudgeNod", false);
		}
		if (Input::GetKey(eKeyCode::N_4))
		{
			mAnimator->Play(L"JudgeShake", false);
		}
		if (Input::GetKey(eKeyCode::N_5))
		{
			mAnimator->Play(L"JudgeSurprisedIdle", true);
		}
		if (Input::GetKey(eKeyCode::N_6))
		{
			mAnimator->Play(L"JudgeSurprisedTalk", true);
		}
		if (Input::GetKey(eKeyCode::N_7))
		{
			mAnimator->Play(L"JudgeSternIdle", true);
		}
		if (Input::GetKey(eKeyCode::N_8))
		{
			mAnimator->Play(L"JudgeSternTalk", true);
		}
		if (Input::GetKey(eKeyCode::N_9))
		{
			mAnimator->Play(L"JudgeThink", false);
		}
	}

	void JudgeScript::Render()
	{
	}

	void JudgeScript::bindEvent()
	{
		mAnimator->GetCompleteEvent(L"JudgeNod") = std::bind(&JudgeScript::returnIdle, this);
		mAnimator->GetCompleteEvent(L"JudgeShake") = std::bind(&JudgeScript::returnIdle, this);
		//mAnimator->GetCompleteEvent(L"MiaFowardIdleBlink") = std::bind(&MiaScript::returnIdle, this);
	}

	void JudgeScript::returnIdle()
	{
		if (mAnimator->GetActiveAnimation()->AnimationName() == L"JudgeNod" ||
			mAnimator->GetActiveAnimation()->AnimationName() == L"JudgeShake")
		{
			mAnimator->Play(L"JudgeIdle", true);
		}
	}

	void JudgeScript::blink()
	{
		if (mAnimator->GetActiveAnimation()->AnimationName() == L"MiaFowardIdle")
		{
			mAnimator->Play(L"MiaFowardIdleBlink", false);
		}
		else if (mAnimator->GetActiveAnimation()->AnimationName() == L"MiaFowardSmileIdle")
		{
			mAnimator->Play(L"MiaFowardSmileIdleBlink", false);
		}
		else if (mAnimator->GetActiveAnimation()->AnimationName() == L"MiaCounselIdle")
		{
			mAnimator->Play(L"MiaCounselIdleBlink", false);
		}
		else if (mAnimator->GetActiveAnimation()->AnimationName() == L"MiaCounselIdleSad")
		{
			mAnimator->Play(L"MiaCounselIdleSadBlink", false);
		}
		else if (mAnimator->GetActiveAnimation()->AnimationName() == L"MiaCounselExasperateIdle")
		{
			mAnimator->Play(L"MiaCounselExasperateIdleBlink", false);
		}
	}
}
