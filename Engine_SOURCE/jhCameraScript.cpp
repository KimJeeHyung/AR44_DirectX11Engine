#include "jhCameraScript.h"
#include "jhTransform.h"
#include "jhGameObject.h"
#include "jhInput.h"
#include "jhTime.h"

namespace jh
{
	CameraScript::CameraScript() :
		Script()
	{
	}

	CameraScript::~CameraScript()
	{
	}

	void CameraScript::Initialize()
	{
	}

	void CameraScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();

		Vector3 pos = tr->GetPosition();

		if (Input::GetKeyState(eKeyCode::D) == PRESSED)
		{
			pos += 10.f * tr->Right() * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::A) == PRESSED)
		{
			pos += 10.f * -tr->Right() * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::W) == PRESSED)
		{
			pos += 10.f * tr->Up() * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::S) == PRESSED)
		{
			pos += 10.f * -tr->Up() * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::Q) == PRESSED)
		{
			pos += 10.f * tr->Foward() * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::E) == PRESSED)
		{
			pos += 10.f * -tr->Foward() * Time::DeltaTime();
		}

		tr->SetPosition(pos);
	}

	void CameraScript::Render()
	{
	}
}

