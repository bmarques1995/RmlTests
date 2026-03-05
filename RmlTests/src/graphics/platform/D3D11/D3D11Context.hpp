#pragma once

#include "GraphicsContext.hpp"

#include <windows.h>
#include <d3d11_4.h>
#include <wrl.h>

using Microsoft::WRL::ComPtr;

namespace RmlTests
{
	class D3D11Context : public GraphicsContext
	{
    public:
        D3D11Context(HWND windowHandle, uint32_t width, uint32_t height);
        ~D3D11Context();

        virtual void SetClearColor(float r, float g, float b, float a) override;
        virtual void ReceiveCommands() override;
        virtual void DispatchCommands() override;
        virtual void Draw(uint32_t elements) override;
        virtual void Present() override;

        virtual void OnResize(uint32_t width, uint32_t height) override;
    
    private:
        ComPtr<ID3D11RenderTargetView> m_RenderTargetView;
        ComPtr<ID3D11Device> m_Device;
        ComPtr<ID3D11DeviceContext> m_Context;
        ComPtr<IDXGISwapChain> m_SwapChain;

        D3D11_VIEWPORT m_Viewport;
        float m_ClearColor[4] = { 0.1f, 0.2f, 0.3f, 1.0f };
	};
}