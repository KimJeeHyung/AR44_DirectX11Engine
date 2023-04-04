#include "jhPlayerScript.h"
#include "jhTransform.h"
#include "jhGameObject.h"
#include "jhInput.h"
#include "jhTime.h"
#include "jhAnimator.h"

namespace jh
{
	PlayerScript::PlayerScript() :
		Script(),
		mAnimator(nullptr)
	{
	}

	PlayerScript::~PlayerScript()
	{
	}

	void PlayerScript::Initialize()
	{
		mAnimator = GetOwner()->GetComponent<Animator>();

		bindEvent();
	}

	void PlayerScript::Update()
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

		mAnimator = GetOwner()->GetComponent<Animator>();
		if (Input::GetKey(eKeyCode::N_1))
		{
			mAnimator->Play(L"PhoenixIdle", false);
		}
		if (Input::GetKey(eKeyCode::N_2))
		{
			mAnimator->Play(L"PhoenixIdleTalk", false);
		}
		if (Input::GetKey(eKeyCode::N_3))
		{
			mAnimator->Play(L"PhoenixIdleNod", true);
		}
		if (Input::GetKey(eKeyCode::N_4))
		{
			mAnimator->Play(L"PhoenixIdleShake", true);
		}
		if (Input::GetKey(eKeyCode::N_5))
		{
			mAnimator->Play(L"PhoenixThink", false);
		}
		if (Input::GetKey(eKeyCode::N_6))
		{
			mAnimator->Play(L"PhoenixThinkTalk", true);
		}
		if (Input::GetKey(eKeyCode::N_7))
		{
			mAnimator->Play(L"PhoenixDeskHit", true);
		}
		if (Input::GetKey(eKeyCode::N_8))
		{
			mAnimator->Play(L"PhoenixDeskIdle", true);
		}
	}

	void PlayerScript::Render()
	{
	}

	void PlayerScript::OnCollisionEnter(Collider2D* collider)
	{
	}

	void PlayerScript::OnCollisionStay(Collider2D* collider)
	{
	}

	void PlayerScript::OnCollisionExit(Collider2D* collider)
	{
	}

	void PlayerScript::bindEvent()
	{
		mAnimator->GetCompleteEvent(L"PhoenixIdle") = std::bind(&PlayerScript::blink, this);
		mAnimator->GetCompleteEvent(L"PhoenixIdleBlink") = std::bind(&PlayerScript::returnIdle, this);
		mAnimator->GetCompleteEvent(L"PhoenixIdleTalk") = std::bind(&PlayerScript::blink, this);
		mAnimator->GetCompleteEvent(L"PhoenixIdleTalkBlink") = std::bind(&PlayerScript::returnIdle, this);
		mAnimator->GetCompleteEvent(L"PhoenixIdleTalk2") = std::bind(&PlayerScript::returnIdle, this);

		mAnimator->GetCompleteEvent(L"PhoenixThink") = std::bind(&PlayerScript::think, this);
		mAnimator->GetCompleteEvent(L"PhoenixThink2") = std::bind(&PlayerScript::think, this);
		mAnimator->GetCompleteEvent(L"PhoenixThink3") = std::bind(&PlayerScript::think, this);
		mAnimator->GetCompleteEvent(L"PhoenixThink4") = std::bind(&PlayerScript::think, this);
		mAnimator->GetCompleteEvent(L"PhoenixThink5") = std::bind(&PlayerScript::think, this);
		mAnimator->GetCompleteEvent(L"PhoenixThink6") = std::bind(&PlayerScript::think, this);

		mAnimator->GetCompleteEvent(L"PhoenixDeskIdle") = std::bind(&PlayerScript::blink, this);
		mAnimator->GetCompleteEvent(L"PhoenixDeskIdleBlink") = std::bind(&PlayerScript::returnIdle, this);
	}

	void PlayerScript::start()
	{
	}

	void PlayerScript::end()
	{
	}

	void PlayerScript::returnIdle()
	{
		if (mAnimator->GetActiveAnimation()->AnimationName() == L"PhoenixIdleBlink")
		{
			mAnimator->Play(L"PhoenixIdle", false);
		}
		else if (mAnimator->GetActiveAnimation()->AnimationName() == L"PhoenixIdleTalkBlink")
		{
			mAnimator->Play(L"PhoenixIdleTalk2", false);
		}
		else if (mAnimator->GetActiveAnimation()->AnimationName() == L"PhoenixIdleTalk2")
		{
			mAnimator->Play(L"PhoenixIdleTalk", false);
		}
		else if (mAnimator->GetActiveAnimation()->AnimationName() == L"PhoenixDeskIdleBlink")
		{
			mAnimator->Play(L"PhoenixDeskIdle", false);
		}
	}

	void PlayerScript::blink()
	{
		if (mAnimator->GetActiveAnimation()->AnimationName() == L"PhoenixIdle")
		{
			mAnimator->Play(L"PhoenixIdleBlink", false);
		}
		else if (mAnimator->GetActiveAnimation()->AnimationName() == L"PhoenixIdleTalk")
		{
			mAnimator->Play(L"PhoenixIdleTalkBlink", false);
		}
		else if (mAnimator->GetActiveAnimation()->AnimationName() == L"PhoenixDeskIdle")
		{
			mAnimator->Play(L"PhoenixDeskIdleBlink", false);
		}
	}

	void PlayerScript::think()
	{
		if (mAnimator->GetActiveAnimation()->AnimationName() == L"PhoenixThink")
		{
			mAnimator->Play(L"PhoenixThink2", false);
		}
		else if (mAnimator->GetActiveAnimation()->AnimationName() == L"PhoenixThink2")
		{
			mAnimator->Play(L"PhoenixThink3", false);
		}
		else if (mAnimator->GetActiveAnimation()->AnimationName() == L"PhoenixThink3")
		{
			mAnimator->Play(L"PhoenixThink4", false);
		}
		else if (mAnimator->GetActiveAnimation()->AnimationName() == L"PhoenixThink4")
		{
			mAnimator->Play(L"PhoenixThink5", false);
		}
		else if (mAnimator->GetActiveAnimation()->AnimationName() == L"PhoenixThink5")
		{
			mAnimator->Play(L"PhoenixThink6", false);
		}
		else if (mAnimator->GetActiveAnimation()->AnimationName() == L"PhoenixThink6")
		{
			mAnimator->Play(L"PhoenixThink", false);
		}
	}
}
