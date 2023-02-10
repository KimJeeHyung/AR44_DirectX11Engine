#pragma once
#include "jhEntity.h"
#include "jhLayer.h"
#include "jhGameObject.h"

namespace jh
{
	using namespace jh::enums;
	class Scene : public Entity
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void AddGameObject(const GameObject* gameObj, const eLayerType type);

	private:
		std::vector<Layer> mLayers;
	};
}
