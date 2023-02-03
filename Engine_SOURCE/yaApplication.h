#pragma once
#include "yaEngine.h"
#include "yaGraphics.h"
#include "yaGraphicDevice_DX11.h"

namespace ya
{
	class Application
	{
	public:
		Application();
		~Application();

		// Running main engine loop
		void Run();

		virtual void Initialize();

		// 게임 로직, 캐릭터 이동 등등
		// CPU Update
		virtual void Update();

		// GPU Update
		virtual void FixedUpdate();

		virtual void Render();

		void SetWindow(HWND hwnd, UINT width, UINT height);
		
		void SetHwnd(HWND hwnd) { mHwnd = hwnd; }
		HWND GetHwnd() { return mHwnd; }
		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }

	private:
		bool initialized = false;
		std::unique_ptr<graphics::GraphicDevice_DX11> graphicDevice;

		HWND mHwnd;
		UINT mWidth;
		UINT mHeight;
	};
}
