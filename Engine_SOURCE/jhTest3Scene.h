#pragma once
#include "jhScene.h"

namespace jh
{
	class Test3Scene : public Scene
	{
	public:
		Test3Scene();
		virtual ~Test3Scene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
	};
}
