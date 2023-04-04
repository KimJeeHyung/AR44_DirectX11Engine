#pragma once
#include "jhScript.h"

namespace jh
{
	class PlayerScript : public Script
	{
	public:
		PlayerScript();
		~PlayerScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

	private:
		void bindEvent();

		void start();
		void end();
		void returnIdle();
		void blink();
		void think();

	private:
		class Animator* mAnimator;
	};
}
