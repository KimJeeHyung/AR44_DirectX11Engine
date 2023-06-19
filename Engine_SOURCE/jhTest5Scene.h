#pragma once
#include "jhScene.h"

namespace jh
{
	class Test5Scene : public Scene
	{
	public:
		Test5Scene();
		virtual ~Test5Scene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
	};
}
