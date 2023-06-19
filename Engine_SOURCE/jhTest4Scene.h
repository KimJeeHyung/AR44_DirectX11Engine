#pragma once
#include "jhScene.h"

namespace jh
{
	class Test4Scene : public Scene
	{
	public:
		Test4Scene();
		virtual ~Test4Scene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
	};
}
