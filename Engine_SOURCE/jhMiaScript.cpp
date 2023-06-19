#include "jhMiaScript.h"
#include "jhTransform.h"
#include "jhGameObject.h"
#include "jhInput.h"
#include "jhTime.h"
#include "jhAnimator.h"

namespace jh
{
	MiaScript::MiaScript() :
		Script(),
		mAnimator(nullptr)
	{
	}

	MiaScript::~MiaScript()
	{
	}

	void MiaScript::Initialize()
	{
		mAnimator = GetOwner()->GetComponent<Animator>();

		bindEvent();
	}

	void MiaScript::Update()
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
			mAnimator->Play(L"MiaFowardIdle", false);
		}
		if (Input::GetKey(eKeyCode::N_2))
		{
			mAnimator->Play(L"MiaFowardTalk", true);
		}
		if (Input::GetKey(eKeyCode::N_3))
		{
			mAnimator->Play(L"MiaFowardGrin", false);
		}
		if (Input::GetKey(eKeyCode::N_4))
		{
			mAnimator->Play(L"MiaFowardSmileIdle", false);
		}
		if (Input::GetKey(eKeyCode::N_5))
		{
			mAnimator->Play(L"MiaFowardSmileTalk", true);
		}
		if (Input::GetKey(eKeyCode::N_6))
		{
			mAnimator->Play(L"MiaFowardShock", true);
		}
		if (Input::GetKey(eKeyCode::N_7))
		{
			mAnimator->Play(L"MiaFowardShockTalk", true);
		}
		if (Input::GetKey(eKeyCode::N_8))
		{
			mAnimator->Play(L"MiaCounselIdle", false);
		}
		if (Input::GetKey(eKeyCode::N_9))
		{
			mAnimator->Play(L"MiaCounselIdleTalk", true);
		}
		if (Input::GetKey(eKeyCode::N_0))
		{
			mAnimator->Play(L"MiaCounselShock", true);
		}
		if (Input::GetKey(eKeyCode::P))
		{
			mAnimator->Play(L"MiaCounselShockTalk", true);
		}
		if (Input::GetKey(eKeyCode::O))
		{
			mAnimator->Play(L"MiaCounselIdleSad", false);
		}
		if (Input::GetKey(eKeyCode::I))
		{
			mAnimator->Play(L"MiaCounselIdleSadTalk", true);
		}
		if (Input::GetKey(eKeyCode::U))
		{
			mAnimator->Play(L"MiaCounselExasperateIdle", false);
		}
		if (Input::GetKey(eKeyCode::Y))
		{
			mAnimator->Play(L"MiaCounselExasperateTalk", true);
		}
	}

	void MiaScript::Render()
	{
	}

	void MiaScript::bindEvent()
	{
		mAnimator->GetCompleteEvent(L"MiaFowardIdle") = std::bind(&MiaScript::blink, this);
		mAnimator->GetCompleteEvent(L"MiaFowardIdleBlink") = std::bind(&MiaScript::returnIdle, this);
		
		mAnimator->GetCompleteEvent(L"MiaFowardGrin") = std::bind(&MiaScript::returnIdle, this);
		
		mAnimator->GetCompleteEvent(L"MiaFowardSmileIdle") = std::bind(&MiaScript::blink, this);
		mAnimator->GetCompleteEvent(L"MiaFowardSmileIdleBlink") = std::bind(&MiaScript::returnIdle, this);

		mAnimator->GetCompleteEvent(L"MiaCounselIdle") = std::bind(&MiaScript::blink, this);
		mAnimator->GetCompleteEvent(L"MiaCounselIdleBlink") = std::bind(&MiaScript::returnIdle, this);
		
		mAnimator->GetCompleteEvent(L"MiaCounselIdleSad") = std::bind(&MiaScript::blink, this);
		mAnimator->GetCompleteEvent(L"MiaCounselIdleSadBlink") = std::bind(&MiaScript::returnIdle, this);
		
		mAnimator->GetCompleteEvent(L"MiaCounselExasperateIdle") = std::bind(&MiaScript::blink, this);
		mAnimator->GetCompleteEvent(L"MiaCounselExasperateIdleBlink") = std::bind(&MiaScript::returnIdle, this);
	}

	void MiaScript::returnIdle()
	{
		if (mAnimator->GetActiveAnimation()->AnimationName() == L"MiaFowardIdleBlink")
		{
			mAnimator->Play(L"MiaFowardIdle", false);
		}
		else if (mAnimator->GetActiveAnimation()->AnimationName() == L"MiaFowardGrin" ||
			mAnimator->GetActiveAnimation()->AnimationName() == L"MiaFowardSmileIdleBlink")
		{
			mAnimator->Play(L"MiaFowardSmileIdle", false);
		}
		else if (mAnimator->GetActiveAnimation()->AnimationName() == L"MiaCounselIdleBlink")
		{
			mAnimator->Play(L"MiaCounselIdle", false);
		}
		else if (mAnimator->GetActiveAnimation()->AnimationName() == L"MiaCounselIdleSadBlink")
		{
			mAnimator->Play(L"MiaCounselIdleSad", false);
		}
		else if (mAnimator->GetActiveAnimation()->AnimationName() == L"MiaCounselExasperateIdleBlink")
		{
			mAnimator->Play(L"MiaCounselExasperateIdle", false);
		}
	}

	void MiaScript::blink()
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
