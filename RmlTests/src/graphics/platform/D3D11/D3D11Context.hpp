#pragma once

#include "GraphicsContext.hpp"

#include <windows.h>
#include <d3d11_4.h>
#include <wrl.h>

using Microsoft::WRL::ComPtr;

namespace RmlTests
{
    struct D3D11RenderControllers
    {
        ID3D11Device* m_Device;
        ID3D11DeviceContext* m_DeviceContext;
    };

	class D3D11Context : public GraphicsContext
	{
    public:
        D3D11Context(HWND windowHandle, uint32_t width, uint32_t height);
        ~D3D11Context();

        void SetClearColor(float r, float g, float b, float a) override;
        void ReceiveCommands() override;
        void DispatchCommands() override;
        void Draw(uint32_t elements) override;
        void Present() override;

        std::any GetControllers() override;

        void OnResize(uint32_t width, uint32_t height) override;
    
    private:
        ComPtr<ID3D11RenderTargetView> m_RenderTargetView;
        ComPtr<ID3D11Device> m_Device;
        ComPtr<ID3D11DeviceContext> m_DeviceContext;
        ComPtr<IDXGISwapChain> m_SwapChain;

        void CreateRTV();

        D3D11_VIEWPORT m_Viewport;
        float m_ClearColor[4] = { 0.1f, 0.2f, 0.3f, 1.0f };
	};
}