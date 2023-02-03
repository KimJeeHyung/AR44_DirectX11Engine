#include "yaGraphicDevice_DX11.h"
#include "yaApplication.h"

extern ya::Application application;

namespace ya::graphics
{
    GraphicDevice_DX11::GraphicDevice_DX11(ValidationMode validationMode)
    {
        // 1. Device와 SwapChain을 생성한다.
        // 2. 백버퍼에 실제로 렌더링할 렌더타겟 뷰를 생성해야 한다.
        // 3. 화면을 클리어 해줘야 한다. 뷰포트를 생성해줘야 한다.
        // 4. 매 프레임마다 위에서 생성한 렌더타겟 뷰에 렌더링해줘야 한다.
        // 5. SwapChain을 이용하여 최종 디바이스(디스플레이)에 화면을 그려줘야 한다.

        HWND hwnd = application.GetHwnd();

        // Device, Device Context
        UINT DeviceFlag = D3D11_CREATE_DEVICE_DEBUG;
        D3D_FEATURE_LEVEL FeatureLevel = (D3D_FEATURE_LEVEL)0;

        HRESULT hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, DeviceFlag,
            nullptr, 0, D3D11_SDK_VERSION, mDevice.GetAddressOf(), &FeatureLevel,
            mContext.GetAddressOf());

        // SwapChain
        DXGI_SWAP_CHAIN_DESC swapChainDesc = {};

        swapChainDesc.OutputWindow = hwnd;
        swapChainDesc.Windowed = true;
        swapChainDesc.BufferCount = 2;

        swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapChainDesc.BufferDesc.Width = application.GetWidth();
        swapChainDesc.BufferDesc.Height = application.GetHeight();
        swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        swapChainDesc.BufferDesc.RefreshRate.Numerator = 240;
        swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
        swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
        swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

        swapChainDesc.SampleDesc.Count = 1;
        swapChainDesc.SampleDesc.Quality = 0;

        if (!CreateSwapChain(&swapChainDesc))
            return;

        // Get RenderTarget for SwapChain
        hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)mRenderTarget.GetAddressOf());

        // Create RenderTarget View
        hr = mDevice->CreateRenderTargetView(mRenderTarget.Get(), nullptr, mRenderTargetView.GetAddressOf());

        D3D11_TEXTURE2D_DESC depthBuffer = {};
        depthBuffer.BindFlags = D3D11_BIND_DEPTH_STENCIL;
        depthBuffer.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
        depthBuffer.Usage = D3D11_USAGE_DEFAULT;
        depthBuffer.CPUAccessFlags = 0;
        depthBuffer.Width = application.GetWidth();
        depthBuffer.Height = application.GetHeight();
        depthBuffer.ArraySize = 1;
        depthBuffer.SampleDesc.Count = 1;
        depthBuffer.SampleDesc.Quality = 0;
        depthBuffer.MipLevels = 1;
        depthBuffer.MiscFlags = 0;

        if (!CreateTexture(&depthBuffer, mDepthStencilBuffer.GetAddressOf()))
            return;

        if (FAILED(mDevice->CreateDepthStencilView(mDepthStencilBuffer.Get(), nullptr,
            mDepthStencilView.GetAddressOf())))
            return;
    }

    GraphicDevice_DX11::~GraphicDevice_DX11()
    {
    }

    bool GraphicDevice_DX11::CreateSwapChain(DXGI_SWAP_CHAIN_DESC* desc)
    {
        Microsoft::WRL::ComPtr<IDXGIDevice> pDXGIDevice = nullptr;
        Microsoft::WRL::ComPtr<IDXGIAdapter> pDXGIAdapter = nullptr;
        Microsoft::WRL::ComPtr<IDXGIFactory> pDXGIFactory = nullptr;

        if (FAILED(mDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)pDXGIDevice.GetAddressOf())))
            return false;

        if (FAILED(pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)pDXGIAdapter.GetAddressOf())))
            return false;

        if (FAILED(pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void**)pDXGIFactory.GetAddressOf())))
            return false;

        if (FAILED(pDXGIFactory->CreateSwapChain(mDevice.Get(), desc, mSwapChain.GetAddressOf())))
            return false;

        return true;
    }

    bool GraphicDevice_DX11::CreateTexture(D3D11_TEXTURE2D_DESC* desc, ID3D11Texture2D** ppTexture2D)
    {
        if (FAILED(mDevice->CreateTexture2D(desc, nullptr, ppTexture2D)))
            return false;

        return true;
    }

    bool GraphicDevice_DX11::CreateBuffer(D3D11_BUFFER_DESC* desc, D3D11_SUBRESOURCE_DATA* data,
        ID3D11Buffer** buffer)
    {
        // System -> GPU
        if (FAILED(mDevice->CreateBuffer(desc, data, buffer)))
            return false;

        return true;
    }

    bool GraphicDevice_DX11::CreateShader()
    {
        return true;
    }

    void GraphicDevice_DX11::Draw()
    {
        FLOAT backgroundColor[4] = { 0.f, 0.5f, 0.f, 1.f };
        mContext->ClearRenderTargetView(mRenderTargetView.Get(), backgroundColor);

        mSwapChain->Present(1, 0);
    }
}
