#include "jhPlayerScript.h"
#include "jhTransform.h"
#include "jhGameObject.h"
#include "jhInput.h"
#include "jhTime.h"

namespace jh
{
	PlayerScript::PlayerScript() :
		Script()
	{
	}

	PlayerScript::~PlayerScript()
	{
	}

	void PlayerScript::Initialize()
	{
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
			pos.z += 6.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		if (Input::GetKey(eKeyCode::UP))
		{
			Vector3 pos = tr->GetPosition();
			pos.z -= 6.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		
		/*Transform* tr = GetOwner()->GetComponent<Transform>();

		Vector3 pos = tr->GetPosition();

		if (Input::GetKeyState(eKeyCode::D) == PRESSED)
		{
			pos.x += 3.f * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::A) == PRESSED)
		{
			pos.x -= 3.f * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::W) == PRESSED)
		{
			pos.y += 3.f * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::S) == PRESSED)
		{
			pos.y -= 3.f * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::Q) == PRESSED)
		{
			pos.z += 3.f * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::E) == PRESSED)
		{
			pos.z -= 3.f * Time::DeltaTime();
		}

		tr->SetPosition(pos);*/
	}

	void PlayerScript::Render()
	{
	}
}
