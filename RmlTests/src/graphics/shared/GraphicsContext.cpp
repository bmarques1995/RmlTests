#include "GraphicsContext.hpp"

#include "D3D11/D3D11Context.hpp"

RmlTests::GraphicsContext* RmlTests::GraphicsContext::Create(GRAPHICS_API api, std::any window, uint32_t width, uint32_t height)
{
    switch (api)
    {
        case GRAPHICS_API::D3D11: return new D3D11Context(std::any_cast<HWND>(window), width, height);
        default: return nullptr;
    }
}
