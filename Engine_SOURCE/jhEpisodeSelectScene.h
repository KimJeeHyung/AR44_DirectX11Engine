#pragma once
#include "jhScene.h"

namespace jh
{
	class EpisodeSelectScene : public Scene
	{
	public:
		EpisodeSelectScene();
		virtual ~EpisodeSelectScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
	};
}
