#include "D3D11Context.hpp"
#include <cassert>
#include <cstdlib>

RmlTests::D3D11Context::D3D11Context(HWND windowHandle, uint32_t width, uint32_t height)
{
    // --- Create D3D11 device + swapchain ---

    DXGI_SWAP_CHAIN_DESC scd = {};
    scd.BufferCount = 2;
    scd.BufferDesc.Width = 0;
    scd.BufferDesc.Height = 0;
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scd.BufferDesc.RefreshRate.Numerator = 60;
    scd.BufferDesc.RefreshRate.Denominator = 1;
    scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scd.OutputWindow = windowHandle;
    scd.SampleDesc.Count = 1;
    scd.SampleDesc.Quality = 0;
    scd.Windowed = TRUE;
    scd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[3] = { D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };

    HRESULT hr = D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        0,
        featureLevelArray,
        3,
        D3D11_SDK_VERSION,
        &scd,
        m_SwapChain.GetAddressOf(),
        m_Device.GetAddressOf(),
        nullptr,
        m_Context.GetAddressOf()
    );

    assert(hr == S_OK);

    // Create Render Target View
    ID3D11Texture2D* backbuffer;
    m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**) &backbuffer);
    m_Device->CreateRenderTargetView(backbuffer, nullptr, m_RenderTargetView.GetAddressOf());
    backbuffer->Release();

    m_Viewport = {};
    m_Viewport.Width = width * 1.0f;
    m_Viewport.Height = height * 1.0f;
    m_Viewport.MinDepth = 0.0f;
    m_Viewport.MaxDepth = 1.0f;
    m_Context->RSSetViewports(1, &m_Viewport);
}

RmlTests::D3D11Context::~D3D11Context()
{
}

void RmlTests::D3D11Context::SetClearColor(float r, float g, float b, float a)
{
    m_ClearColor[0] = r;
    m_ClearColor[1] = g;
    m_ClearColor[2] = b;
    m_ClearColor[3] = a;
}

void RmlTests::D3D11Context::ReceiveCommands()
{
    m_Context->OMSetRenderTargets(1, m_RenderTargetView.GetAddressOf(), nullptr);
    m_Context->ClearRenderTargetView(m_RenderTargetView.Get(), m_ClearColor);
}

void RmlTests::D3D11Context::DispatchCommands()
{
}

void RmlTests::D3D11Context::Draw(uint32_t elements)
{
}

void RmlTests::D3D11Context::Present()
{
    m_SwapChain->Present(1, 0);
}

void RmlTests::D3D11Context::OnResize(uint32_t width, uint32_t height)
{
    m_RenderTargetView.Reset();
    m_RenderTargetView = nullptr;
    HRESULT hr = m_SwapChain->ResizeBuffers(0, width, height, DXGI_FORMAT_UNKNOWN, 0);
    // Create Render Target View
    ID3D11Texture2D* backbuffer;
    m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backbuffer);
    m_Device->CreateRenderTargetView(backbuffer, nullptr, m_RenderTargetView.GetAddressOf());
    backbuffer->Release();

    m_Viewport = {};
    m_Viewport.Width = width * 1.0f;
    m_Viewport.Height = height * 1.0f;
    m_Viewport.MinDepth = 0.0f;
    m_Viewport.MaxDepth = 1.0f;
    m_Context->RSSetViewports(1, &m_Viewport);
}
