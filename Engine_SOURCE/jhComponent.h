#pragma once
#include "jhMath.h"
#include "jhEntity.h"

using namespace jh::enums;
namespace jh
{
	class GameObject;
	class Component : public Entity
	{
	public:
		Component(eComponentType type);
		virtual ~Component();

		virtual void Initialize() = 0;
		virtual void Update() = 0;
		virtual void FixedUpdate() = 0;
		virtual void Render() = 0;

		eComponentType GetOrder() { return mType; }

		GameObject* GetOwner() { return mOwner; }
		void SetOwner(GameObject* owner) { mOwner = owner; }

	private:
		const eComponentType mType;
		GameObject* mOwner;
	};
}

