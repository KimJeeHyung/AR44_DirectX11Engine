#pragma once
#include "jhGameObject.h"

namespace jh
{
	class Layer
	{
	public:
		Layer();
		virtual ~Layer();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void AddGameObject(const GameObject* gameObject);

	private:
		std::vector<GameObject*> mGameObjects;
	};
}
