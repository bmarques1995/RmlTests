#include "D3D11Context.hpp"
#include <cassert>
#include <cstdlib>

RmlTests::D3D11Context::D3D11Context(HWND windowHandle, uint32_t width, uint32_t height)
{
    // --- Create D3D11 device + swapchain ---

    DXGI_SWAP_CHAIN_DESC scd = {};
    scd.BufferCount = 2;
    scd.BufferDesc.Width = width;
    scd.BufferDesc.Height = height;
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scd.OutputWindow = windowHandle;
    scd.SampleDesc.Count = 1;
    scd.Windowed = TRUE;
    scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    HRESULT hr = D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        0,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        &scd,
        m_SwapChain.GetAddressOf(),
        m_Device.GetAddressOf(),
        nullptr,
        m_Context.GetAddressOf()
    );

    assert(hr == S_OK);

    // Create Render Target View
    ComPtr<ID3D11Texture2D> backbuffer;
    m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)backbuffer.GetAddressOf());
    if (backbuffer.Get() != nullptr)
    {
        m_Device->CreateRenderTargetView(backbuffer.Get(), nullptr, m_RenderTargetView.GetAddressOf());
        backbuffer->Release();
    }
    else
    {
        exit(65);
    }

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
    m_RenderTargetView->Release();
    m_SwapChain->ResizeBuffers(0, width, height, DXGI_FORMAT_UNKNOWN, 0);
    // Create Render Target View
    ComPtr<ID3D11Texture2D> backbuffer;
    m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)backbuffer.GetAddressOf());
    if (backbuffer.Get() != nullptr)
    {
        m_Device->CreateRenderTargetView(backbuffer.Get(), nullptr, m_RenderTargetView.GetAddressOf());
        backbuffer->Release();
    }
    else
    {
        exit(65);
    }
}
