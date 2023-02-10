#pragma once
#include "jhEntity.h"

namespace jh
{
	class GameObject;
	class Component
	{
	public:
		enum class eType
		{
			None,
			Transform,
			Camera,

			//render
			Mesh,
			SkyBox,
			Decal,

			Script,
			End,
		};

		Component();
		virtual ~Component();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
		const eType mType;
		GameObject* mOwner;
	};
}

