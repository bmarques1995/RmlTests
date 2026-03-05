// RmlTests.cpp: define o ponto de entrada para o aplicativo.
//

#include "RmlTests.hpp"
#include <windows.h>
#include <SDL3/SDL.h>
#include <RmlUi/Core.h>
#include <RmlUi/Debugger.h>
#include "GraphicsContext.hpp"
#include <memory>

int main(int argc, char** argv)
{
    int width = 1280;
    int height = 720;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL Init failed: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "SDL3 + D3D11",
        width,
        height,
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY
    );

    if (!window) {
        printf("Window creation failed: %s\n", SDL_GetError());
        return -1;
    }

    // Get Win32 HWND from SDL3
    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    HWND hwnd = (HWND)SDL_GetPointerProperty(
        props,
        SDL_PROP_WINDOW_WIN32_HWND_POINTER,
        NULL
    );

    if (!hwnd) {
        printf("Failed to get HWND\n");
        return -1;
    }

    //// --- Create D3D11 device + swapchain ---

    //DXGI_SWAP_CHAIN_DESC scd = {};
    //scd.BufferCount = 2;
    //scd.BufferDesc.Width = width;
    //scd.BufferDesc.Height = height;
    //scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    //scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    //scd.OutputWindow = hwnd;
    //scd.SampleDesc.Count = 1;
    //scd.Windowed = TRUE;
    //scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    //ID3D11Device* m_Device = nullptr;
    //ID3D11DeviceContext* m_Context = nullptr;
    //IDXGISwapChain* m_SwapChain = nullptr;

    //HRESULT hr = D3D11CreateDeviceAndSwapChain(
    //    nullptr,
    //    D3D_DRIVER_TYPE_HARDWARE,
    //    nullptr,
    //    0,
    //    nullptr,
    //    0,
    //    D3D11_SDK_VERSION,
    //    &scd,
    //    &m_SwapChain,
    //    &m_Device,
    //    nullptr,
    //    &m_Context
    //);

    //if (FAILED(hr)) {
    //    printf("Failed to create D3D11 device\n");
    //    return -1;
    //}

    //// Create Render Target View
    //ID3D11Texture2D* backbuffer = nullptr;
    //m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backbuffer);

    //ID3D11RenderTargetView* m_RenderTargetView = nullptr;
    //m_Device->CreateRenderTargetView(backbuffer, nullptr, &m_RenderTargetView);
    //backbuffer->Release();

    //D3D11_VIEWPORT m_Viewport = {};
    //m_Viewport.Width = width * 1.0f;
    //m_Viewport.Height = height * 1.0f;
    //m_Viewport.MinDepth = 0.0f;
    //m_Viewport.MaxDepth = 1.0f;
    //m_Context->RSSetViewports(1, &m_Viewport);

    RmlTests::GRAPHICS_API api = RmlTests::GRAPHICS_API::D3D11;
    std::shared_ptr<RmlTests::GraphicsContext> context;
    context.reset(RmlTests::GraphicsContext::Create(api, hwnd, width, height));
    context->SetClearColor(.0f, .5f, .25f, 1.0f);

    // --- Main Loop ---
    bool running = true;
    SDL_Event event;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
                running = false;
            if (event.type == SDL_EVENT_WINDOW_RESIZED && event.window.windowID == SDL_GetWindowID(window))
                context->OnResize(event.window.data1, event.window.data2);
        }
        context->ReceiveCommands();
        context->DispatchCommands();
        context->Present();
        
    }

    context.reset();
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
