#include "yaApplication.h"
#include "yaRenderer.h"

namespace ya
{
	using namespace graphics;

	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		Update();
		FixedUpdate();
		Render();
	}

	void Application::Initialize()
	{
		renderer::Initialize();
	}

	void Application::Update()
	{
	}

	void Application::FixedUpdate()
	{
	}

	void Application::Render()
	{
		graphicDevice->Draw();
	}

	void Application::SetWindow(HWND hwnd, UINT width, UINT height)
	{
		if (graphicDevice == nullptr)
		{
			mHwnd = hwnd;
			mWidth = width;
			mHeight = height;

			ValidationMode validationMode = ValidationMode::Disabled;
			graphicDevice = std::make_unique<GraphicDevice_DX11>();
			graphics::GetDevice() = graphicDevice.get();
		}

		RECT rt = { 0, 0, (LONG)width, (LONG)height };
		AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
		SetWindowPos(mHwnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
		ShowWindow(mHwnd, true);
		UpdateWindow(mHwnd);
	}
}
