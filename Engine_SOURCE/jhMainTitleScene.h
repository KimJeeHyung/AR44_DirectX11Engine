#pragma once
#include "jhScene.h"

namespace jh
{
	class MainTitleScene : public Scene
	{
	public:
		MainTitleScene();
		virtual ~MainTitleScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
		GameObject* mFadeObj;
	};
}
