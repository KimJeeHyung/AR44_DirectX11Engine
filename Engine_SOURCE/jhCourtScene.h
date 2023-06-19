#pragma once
#include "jhScene.h"

namespace jh
{
	class CourtScene : public Scene
	{
	public:
		CourtScene();
		virtual ~CourtScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
	};
}
